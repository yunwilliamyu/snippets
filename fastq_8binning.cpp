#include <cstdio>
#include <iostream>
#include <string>


int bin8(int q) {
    if (q==50) {
        return 50;
    } else if (q>39) {
        return 40;
    } else if (q>34) {
        return 37;
    } else if (q>29) {
        return 33;
    } else if (q>24) {
        return 27;
    } else if (q>19) {
        return 22;
    } else if (q>9) {
        return 15;
    } else if (q>2) {
        return 6;
    } else if (q==2) {
        return 2;
    } else {
        return q;
    }
}

int main() {
    std::string line;
    //int c;
    //int q;

    int i = 0;
    while (std::getline(std::cin, line))
    {
        if (i++%4 == 3) {
            for (std::string::iterator it = line.begin(); it != line.end(); it++) {
                *it = bin8(*it - 33) + 33;
            }
        }
        std::cout << line << std::endl;
    }

    /*do {
        c = getchar();
        q = c - 33;
        putchar(bin8(q) + 33);
    } while (c != EOF); */
    return 0;
}
