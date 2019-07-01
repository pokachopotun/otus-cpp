#include <hello_world.h>

#include <iostream>

int main(int, char**) {
    
    HelloWorld::HelloWorld();
    std::cout << HelloWorld::GetVersion() << std::endl;

    return 0;
}
