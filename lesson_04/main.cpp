#include <print_ip.h>

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

int main(int, char**) {
    cout << NPrintIP::PrintIp(char(-1)) << endl;
    cout << NPrintIP::PrintIp(short(0)) << endl;
    cout << NPrintIP::PrintIp(int(1234)) << endl;
    cout << NPrintIP::PrintIp(int(2130706433)) << endl;
    cout << NPrintIP::PrintIp(long(8875824491850138409)) << endl;
    cout << NPrintIP::PrintIp(std::string("trololo")) << endl;
    cout << NPrintIP::PrintIp(std::vector<int>{0, 1, 2, 3}) << endl;
    cout << NPrintIP::PrintIp(std::list<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) << endl;
    return 0;
}
