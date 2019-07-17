#include "ip_filter.h"

#include <version.h>

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

namespace NIpFilter {

    ostream& operator<<(ostream& out, const IpAddress& ip) {
        out << ip[0];
        for(size_t i = 1; i < ip.size(); i++) {
            out << "." << ip[i];
        }
        return out;
    }

    istream& operator>>(istream& in, IpAddress& ip) {
        in >> ip[0];
        char c;
        for(size_t i = 1; i < ip.size(); i++) {
            in >> c >> ip[i];
        }
        return in;
    }

    template<typename T>
    void PrintIpsByCondition(ostream& out, const vector<T>& vec, function<bool(const T&)> condition) {
        for(const T& elem : vec) {
            if(condition(elem)) {
                out << elem << endl;
            }
        }
    }

    istream& FilterIps(istream& in, ostream& out) {
        string line;
        vector<IpAddress> ips;
        while(getline(in, line)) {
            stringstream lineStream(line);
            IpAddress ip;
            lineStream >> ip;
            ips.push_back(move(ip));
        }

        sort(ips.rbegin(), ips.rend());

        PrintIpsByCondition<IpAddress>(out, ips, [](const IpAddress& ) { return true;});
        PrintIpsByCondition<IpAddress>(out, ips, [](const IpAddress& ip) { return ip[0] ==  1;});
        PrintIpsByCondition<IpAddress>(out, ips, [](const IpAddress& ip) { return ip[0] ==  46 && ip[1] == 70;});
        PrintIpsByCondition<IpAddress>(out, ips, [](const IpAddress& ip) { return find(ip.begin(), ip.end(), 46) != ip.end();});
        return in;
    }

    int GetVersion() {
        return PROJECT_VERSION_PATCH;
    }
}
