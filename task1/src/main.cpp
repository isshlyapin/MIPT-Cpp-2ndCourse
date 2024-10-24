#include <iostream>
#include <vector>

#include "utils.hpp"

int main() {
    size_t cacheSize{0};
    size_t amountPages{0};
    std::vector<int> keys;

    getInputData(cacheSize, amountPages, keys); 

    int hits = -1;
#ifdef MY_CACHE_2Q
    hits = checkCache2Q(cacheSize, amountPages, keys);
#elif MY_CACHE_BELADY
    //hits = checkCacheBelady(cacheSize, amountPages, keys);
    hits = checkCacheBelady2(cacheSize, keys);
#endif

    std::cout << hits << std::endl;

    return 0;
}
