#include <iostream>
#include <vector>

#include "utils.hpp"

// slow get page imitation
static int slow_get_page_int(int key) { return key; }

int main() {
    size_t cacheSize{0};
    size_t amountPages{0};
    std::vector<int> keys;

    getInputData(cacheSize, amountPages, keys); 

    int hits = -1;
#ifdef MY_CACHE_2Q
    hits = checkCache2Q(cacheSize, amountPages, keys);
#elif MY_CACHE_BELADY
    /*hits = checkCacheBelady(cacheSize, amountPages, keys, slow_get_page_int);*/
    hits = checkCacheBelady2(cacheSize, keys);
#endif

    std::cout << hits << std::endl;

    return 0;
}
