#include <gtest/gtest.h>

#include "cache_2q.hpp"
#include "test_utils.hpp"

TEST(Cache, lookup_update) {
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