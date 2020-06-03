#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <type_traits>
#include <bitset>

namespace NPrintIP {

    template<typename T, typename = void>
    struct is_iterable : std::false_type {};

    template<typename T>
    struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin() != std::declval<T>().end()),
                                      decltype(std::declval<T>().size()),
                                      decltype(++std::declval<T>().begin())>> : std::true_type {};

    template<typename TInteger, typename std::enable_if<std::is_integral<TInteger>::value, int>::type = 0>
    std::string PrintIp(TInteger value) {

        const size_t bytes = sizeof(value);
        using TBits = std::bitset<bytes * 8>;
        const TBits bits(value);
        TBits mask(255);
        std::stringstream ss;
        for (size_t i = 0; i < bytes; ++i) {
            const size_t shift = (bytes - 1 - i) * 8;
            TBits byte = (bits & (mask << shift)) >> shift;
            ss << byte.to_ulong();
            if (i != bytes - 1) {
                ss << ".";
            }
        }
        return ss.str();
    }

    template<typename TIterable, typename std::enable_if<is_iterable<TIterable>::value, int>::type = 0>
    std::string PrintIp(const TIterable& container) {
        size_t cnt = 0;
        std::stringstream ss;
        for (auto it = container.begin(); it != container.end(); ++it) {
            ss << *it;
            ++cnt;
            if (cnt < container.size()) {
                ss << ".";
            }
        }
        return ss.str();
    }

    template<>
    std::string PrintIp(const std::string& value) {
        return value;
    }

}
