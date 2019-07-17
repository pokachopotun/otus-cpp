#pragma once

#include <iostream>
#include <array>

namespace NIpFilter {

    using IpAddress = std::array<int,4>;

    std::ostream& operator<<(std::ostream& out, const IpAddress& ip);
    std::istream& operator>>(std::istream& in, IpAddress& ip);

    std::istream& FilterIps(std::istream& in, std::ostream& out);

    int GetVersion();

}
