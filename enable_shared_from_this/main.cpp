#include <iostream>
#include <future>
#include <memory>
#include <thread>
#include <vector>

using namespace std;

class TAsyncTaskContext : public std::enable_shared_from_this<TAsyncTaskContext> {
public:
    void KeepAlive() {
        auto&& keepMeAliveLongEnough = [this, thisPtr = shared_from_this()]() {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            cout << "DoJob" << endl;
        };

        keepMeAliveLongEnough();
    }
};

class TContextOwner {
public:
    TContextOwner() 
        : Ctx(std::make_shared<TAsyncTaskContext>())
    {

    }

    TAsyncTaskContext* GetContext() {
        return Ctx.get();
    }

private:
    std::shared_ptr<TAsyncTaskContext> Ctx;
};

class TContextUser {
public:
    TContextUser(TAsyncTaskContext* ctx) 
        : Ctx(ctx) 
    {

    }

    std::vector<std::thread> MakeLotsOfThreads(size_t threadCount) {
        auto&& threadFunction = [ctx = Ctx]() {
            ctx->KeepAlive();
        };

        std::vector<std::thread> workers;
        for (int i = 0; i < threadCount; i++) {
            std::thread w(threadFunction);
            workers.push_back(std::move(w));
        }

        return workers;
    }

private:
    TAsyncTaskContext* Ctx = nullptr;
};

std::vector<std::thread> MakeLotsOfThreads(size_t threadCount) {
    TContextOwner owner;
    TAsyncTaskContext* ctx = owner.GetContext();
    return TContextUser(ctx).MakeLotsOfThreads(threadCount);
}

int main() {
    auto workers = MakeLotsOfThreads(3);
    cout << "MakeLotsOfThreads exited " << endl;
    for (auto& worker : workers) {
        worker.join();
    }
    return 0;
}
