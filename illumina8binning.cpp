/* Copyright (c) 2017 Yun William Yu
 * Released under CC0 1.0 Universal. */
/* illumina8binning.cpp */
/* Simulates Illumina 8 binning for a FASTQ file, described in
 * http://www.illumina.com/documents/products/whitepapers/whitepaper_datacompression.pdf */

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
    return 0;
}
