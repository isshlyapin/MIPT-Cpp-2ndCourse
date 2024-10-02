#include <gtest/gtest.h>


#include "utils.hh"
#include "test_utils.hh"

TEST(Cache, amount_hits) {
    size_t cacheSize{5};
    size_t amountPages{10};
    std::vector<int> keys1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1};
    std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3};
    std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4};
    
    EXPECT_EQ(checkCache(cacheSize, amountPages, keys1, getPage), 0);
    EXPECT_EQ(checkCache(cacheSize, amountPages, keys2, getPage), 9);
    EXPECT_EQ(checkCache(cacheSize, amountPages, keys3, getPage), 3);
    EXPECT_EQ(checkCache(cacheSize, amountPages, keys4, getPage), 4);
    EXPECT_EQ(checkCache(cacheSize, amountPages, keys5, getPage), 5);
}