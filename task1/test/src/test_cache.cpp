#include <gtest/gtest.h>
#include <vector>

#include <iostream>

#include "cache_2q.hpp"
#include "cache_belady.hpp"
#include "test_utils.hpp"

TEST(Cache, Cache2Q) {
    caches::Cache2Q<int> cache{10};
    
    // Testing adding a new page to a not full cacheIn
    EXPECT_FALSE(cache.lookupUpdate(1, getPage));
    EXPECT_EQ(cache.getCacheIn().front().first, 1);
    
    EXPECT_FALSE(cache.lookupUpdate(2, getPage));
    EXPECT_EQ(cache.getCacheIn().front().first, 2);
    
    // Testing moving the last element from cacheIn to cacheOut, when the first one is full
    EXPECT_FALSE(cache.lookupUpdate(3, getPage));
    EXPECT_EQ(cache.getCacheOut().front().first, 1);

    EXPECT_FALSE(cache.lookupUpdate(4, getPage));
    EXPECT_EQ(cache.getCacheOut().front().first, 2);

    EXPECT_FALSE(cache.lookupUpdate(5, getPage));
    EXPECT_FALSE(cache.lookupUpdate(6, getPage));
    EXPECT_FALSE(cache.lookupUpdate(7, getPage));
    EXPECT_FALSE(cache.lookupUpdate(8, getPage));

    // Testing overflow cacheOut 
    EXPECT_FALSE(cache.lookupUpdate(9, getPage));
    EXPECT_EQ(cache.getCacheOut().back().first, 2);
    
    // Testing moving ppage from cacheOut to cacheHot
    EXPECT_TRUE(cache.lookupUpdate(4, getPage));
    EXPECT_EQ(cache.getCacheHot().front().first, 4);

    EXPECT_TRUE(cache.lookupUpdate(5, getPage));
    EXPECT_EQ(cache.getCacheHot().front().first, 5);

    // Testing moving a page to the top of the cacheIn
    EXPECT_EQ(cache.getCacheIn().front().first, 9);    
    EXPECT_TRUE(cache.lookupUpdate(8, getPage));
    EXPECT_EQ(cache.getCacheIn().front().first, 8);

    // Testing moving a page to the top of the cacheHot
    EXPECT_EQ(cache.getCacheHot().front().first, 5);
    EXPECT_TRUE(cache.lookupUpdate(4, getPage));
    EXPECT_EQ(cache.getCacheHot().front().first, 4);
}

TEST(Cache, CacheBelady) {
    caches::CacheBelady<int> cache{5};

    std::vector<int> keys{1, 2, 3, 4, 5, 6, 6, 1, 2, 5, 4, 3};
    
    EXPECT_FALSE(cache.lookupUpdate(1, std::span<int>(keys).subspan(1), getPage));
    EXPECT_FALSE(cache.lookupUpdate(2, std::span<int>(keys).subspan(2), getPage));
    EXPECT_FALSE(cache.lookupUpdate(3, std::span<int>(keys).subspan(3), getPage));
    EXPECT_FALSE(cache.lookupUpdate(4, std::span<int>(keys).subspan(4), getPage));
    EXPECT_FALSE(cache.lookupUpdate(5, std::span<int>(keys).subspan(5), getPage));

    EXPECT_FALSE(cache.lookupUpdate(6, std::span<int>(keys).subspan(6), getPage));
    EXPECT_FALSE(cache.lookupUpdate(3, std::span<int>(keys).subspan(7), getPage));
    EXPECT_FALSE(cache.lookupUpdate(6, std::span<int>(keys).subspan(8), getPage));

    EXPECT_FALSE(cache.lookupUpdate(8, std::span<int>(keys).subspan(9), getPage));
    EXPECT_FALSE(cache.lookupUpdate(8, std::span<int>(keys).subspan(10), getPage));
}