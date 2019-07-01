#include <hello_world.h>

#include <iostream>

int main(int, char**) {
    
    NHelloWorld::HelloWorld();
    std::cout << NHelloWorld::GetVersion() << std::endl;

    return 0;
}
