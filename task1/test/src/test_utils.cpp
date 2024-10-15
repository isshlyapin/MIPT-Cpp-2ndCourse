#include <gtest/gtest.h>

#include "utils.hpp"
#include "test_utils.hpp"

TEST(Cache, amount_hits_2q) {
    size_t cacheSize{5};
    size_t amountPages{10};
    std::vector<int> keys1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1};
    std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3};
    std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4};
    
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys1, getPage), 0);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys2, getPage), 9);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys3, getPage), 3);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys4, getPage), 4);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys5, getPage), 5);
}

TEST(Cache, amount_hits_belady) {
    size_t cacheSize{5};
    size_t amountPages{12};
    std::vector<int> keys1{1, 2, 3, 4, 5, 6, 6, 1, 2, 5, 4, 3};
    std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1, 8, 8};
    std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3, 7, 8};
    std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4, 1, 1};
    
    EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys1, getPage), 5);
    EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys2, getPage), 11);
    EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys3, getPage), 5);
    EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys4, getPage), 4);
    EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys5, getPage), 7);
}