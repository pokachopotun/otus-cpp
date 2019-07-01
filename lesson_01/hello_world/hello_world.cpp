#include "helloworld.h"

#include <version.h>

#include <iostream>

namespace HelloWorld {

    void HelloWorld() {
        std::cout << "Hello, World!" << std::endl;
    }

    int GetVersion() {
        return PROJECT_VERSION_PATCH;
    }

}
