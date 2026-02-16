//
// Created by Brayhan De Aza on 12/6/25.
//

#include "print.h"
#include <iostream>

extern "C" void yogi_print(const char* message) {
    std::cout << message << std::endl;
}
