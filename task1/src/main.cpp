#include <iostream>
#include <vector>

#include "utils.hpp"

int main() {
    size_t cacheSize{0};
    size_t amountPages{0};
    std::vector<int> keys;

    getInputData(cacheSize, amountPages, keys);

    int hits2Q     = checkCache2Q(cacheSize, amountPages, keys, slow_get_page_int);
    // int hitsBelady = checkCacheBelady(cacheSize, amountPages, keys, slow_get_page_int);

    // std::cout << "checkCache2Q:     " << hits2Q     << std::endl;
    // std::cout << "checkCacheBelady: " << hitsBelady << std::endl;
    std::cout << hits2Q << std::endl;

    return 0;
}