#include <iostream>
#include "spdlog/spdlog.h"

int main() {
    std::cout << "hello" << std::endl;
    spdlog::info("hello");
    return 0;
}