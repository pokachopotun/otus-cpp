#pragma once

#include <cstdlib>
#include <new>

namespace NCustomAllocator {

int GetVersion();

template<typename T, std::size_t N>
class TCustomAllocator {
private:
    void* Pre = nullptr;
    std::size_t Last = 0;

public:
    using value_type = T;

    template<class Type>
    struct rebind {
        using other = TCustomAllocator<Type, N>;
    };

    TCustomAllocator() {
        Pre = std::malloc(N * sizeof(value_type));
        if (!Pre) {
            throw std::bad_alloc();
        }
    }

    value_type* allocate(std::size_t n) {
        if (Last + n <= N) {
            std::size_t pos = Last;
            Last += n;
            return reinterpret_cast<value_type*>(Pre) + pos;
        }
        throw std::bad_alloc();
    }

    void deallocate(value_type*, std::size_t) {

    }

    ~TCustomAllocator() {
        free(Pre);
    }
};

/*
template<class T, class U>
bool operator==(const TCustomAllocator<T>&, const TCustomAllocator<U>&) noexcept {
    return true;
}

template<class T, class U>
bool operator!=(const TCustomAlocator<T>& x, const TCustomAllocator<U>& y) noexcept {
    return !(x == y);
} */

}
