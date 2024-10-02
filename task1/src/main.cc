#include <iostream>

#include "utils.hh"

int main() {
    size_t cacheSize{0};
    size_t amountPages{0};
    std::vector<int> keys;

    getInputData(cacheSize, amountPages, keys);

    int hits = checkCache(cacheSize, amountPages, keys, slow_get_page_int);

    std::cout << "= " << hits << std::endl;

    return 0;
}