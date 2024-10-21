#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Cache, amount_hits_2q) {
    size_t cacheSize{5};
    size_t amountPages{10};
    std::vector<int> keys1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1};
    std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3};
    std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4};

    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys1), 0);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys2), 9);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys3), 3);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys4), 4);
    EXPECT_EQ(checkCache2Q(cacheSize, amountPages, keys5), 5);
}

// TEST(Cache, amount_hits_belady) {
//     size_t cacheSize{5};
//     size_t amountPages{12};
//     std::vector<int> keys1{1, 2, 3, 4, 5, 6, 6, 1, 2, 5, 4, 3};
//     std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//     std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1, 8, 8};
//     std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3, 7, 8};
//     std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4, 1, 1};

//     EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys1), 5);
//     EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys2), 11);
//     EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys3), 5);
//     EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys4), 4);
//     EXPECT_EQ(checkCacheBelady(cacheSize, amountPages, keys5), 7);
// }

TEST(Cache, amount_hits_belady2_keys1) {
    size_t cacheSize{5};
    std::vector<int> keys1{1, 2, 3, 4, 5, 6, 6, 1, 2, 5, 4, 3};
    EXPECT_EQ(checkCacheBelady2(cacheSize, keys1), 5);
}

TEST(Cache, amount_hits_belady2_keys2) {
    size_t cacheSize{5};
    std::vector<int> keys2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
    EXPECT_EQ(checkCacheBelady2(cacheSize, keys2), 11);
}

TEST(Cache, amount_hits_belady2_keys3) {
    size_t cacheSize{5};
    std::vector<int> keys3{1, 2, 3, 1, 4, 5, 1, 6, 3, 1, 8, 8};
    EXPECT_EQ(checkCacheBelady2(cacheSize, keys3), 5);
}

TEST(Cache, amount_hits_belady2_keys4) {
    size_t cacheSize{5};
    std::vector<int> keys4{1, 2, 3, 4, 1, 4, 5, 2, 6, 3, 7, 8};
    EXPECT_EQ(checkCacheBelady2(cacheSize, keys4), 4);
}

TEST(Cache, amount_hits_belady2_keys5) {
    size_t cacheSize{5};
    std::vector<int> keys5{1, 2, 3, 4, 4, 1, 2, 3, 5, 4, 1, 1};
    EXPECT_EQ(checkCacheBelady2(cacheSize, keys5), 7);
}
