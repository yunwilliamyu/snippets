#include <cstdio>
#include <iostream>
#include <string>


int main() {
    std::string line;
    int i = 0;
    while (std::getline(std::cin, line))
    {
        if (i++%4 == 3) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}
