#include <custom_allocator.h>
#include <custom_linked_list.h>

#include <iostream>
#include <map>

using namespace std;

int main(int, char**) {

    std::cout << NCustomAllocator::GetVersion() << std::endl;

    {
        std::map<int, int> m;
        m[0] = 1;
        for (int i = 1, fac = 1; i <= 9; ++i) {
            fac *= i;
            m.emplace(i, fac);
        }
        cout << "std::map values: ";
        for (const pair<const int, int>& p : m) {
            cout << p.second << " ";
        }
        cout << endl;
    }

    {
        std::map<int, int, std::less<int>, NCustomAllocator::TCustomAllocator<std::pair<const int, int>, 10>> m;
        m[0] = 1;
        for (int i = 1, fac = 1; i <= 9; ++i) {
            fac *= i;
            m.emplace(i, fac);
        }

        cout << "std::map with TCustomAllocator values: ";
        for (const pair<const int, int>& p : m) {
            cout << p.second << " ";
        }
        cout << endl;
    }

    {
        NCustomAllocator::TCustomLinkedList<int> lst;
        for (int i = 0; i <= 9; ++i) {
            lst.Add(i);
        }

        cout << "TCustomLinkedList values: ";
        for (const int x : lst) {
            cout << x << " ";
        }
        cout << endl;
    }

    {
        NCustomAllocator::TCustomLinkedList<int, NCustomAllocator::TCustomAllocator<int, 10>> lst;
        for (int i = 0; i <= 9; ++i) {
            lst.Add(i);
        }

        cout << "TCustomLinkedList with TCustomAllocator values: ";
        for (const int x : lst) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
