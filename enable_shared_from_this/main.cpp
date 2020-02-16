#include <iostream>
#include <future>
#include <memory>
#include <thread>
#include <vector>

using namespace std;

// it is in .cpp for any reason
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

// it is in .h
std::vector<std::thread> MakeLotsOfThreads(size_t threadCount) {
    auto ctx = std::make_shared<TAsyncTaskContext>();

    auto&& threadFunction = [ctx = ctx.get()]() {
        ctx->KeepAlive();
    };

    std::vector<std::thread> workers;
    for (int i = 0; i < threadCount; i++) {
        std::thread w(threadFunction);
        workers.push_back(std::move(w));
    }

    return workers;
}

int main() {
    auto workers = MakeLotsOfThreads(3);
    cout << "MakeLotsOfThreads exited " << endl;
    for (auto& worker : workers) {
        worker.join();
    }
    return 0;
}
