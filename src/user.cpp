#include <print>
#include <iostream>
#include <cstdlib>

#include "user.hpp"

void sysOpera() {
    int opera;
    while (std::cin >> opera && opera != 0) {
        system("cls");
        std::print("{}\n", opera);
    }
}