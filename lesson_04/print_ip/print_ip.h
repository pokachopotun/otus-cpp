#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <type_traits>
#include <bitset>
/** @brief namespace containing my solution for homework #4
    of C++ Developer course by Otus.

    Detailed description follows here.
    @author pokachopotun
    @date June 2020
    */
namespace NPrintIP {

    /**
        \brief Metafunction checks if provided type is iterable.
        i.e. has .begin(), .end(), .size()
        and provides iterator with:
        operator++(), operator!=() implemented
    */
    template<typename T, typename = void>
    struct is_iterable : std::false_type {};

    template<typename T>
    struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin() != std::declval<T>().end()),
                                      decltype(std::declval<T>().size()),
                                      decltype(++std::declval<T>().begin())>> : std::true_type {};


    /**
        \brief Print IP address. Integral numeric typesbers version;
        \param value of Integral type.
        \return String representation of respecting IP address
    */
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

    /**
        \brief Print IP address. Iterable container overload;
        \param container - iterable container
        \return String representation of respecting IP address
    */
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

    /**
        \brief Print IP address. std::string overload;
        \param value - a string
        \return value
    */
    template<>
    std::string PrintIp(const std::string& value) {
        return value;
    }

}
