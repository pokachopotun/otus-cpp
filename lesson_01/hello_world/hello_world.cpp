#include "hello_world.h"

#include <version.h>

#include <iostream>

namespace NHelloWorld {

    void HelloWorld() {
        std::cout << "Hello, World!" << std::endl;
    }

    int GetVersion() {
        return PROJECT_VERSION_PATCH;
    }

}
