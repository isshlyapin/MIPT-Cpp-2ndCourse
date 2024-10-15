// cache.hh
#pragma once

#include <list>
#include <unordered_map>
#include <cstddef>
#include <stdexcept>

namespace caches {

template <typename T, typename K = int>
class Cache2Q {
private:
    using List   = typename std::list<std::pair<K, T>>;
    using ListIt = typename List::iterator;
    using Map    = typename std::unordered_map<K, ListIt>;

public:
    Cache2Q(size_t sz);

    template <typename F>
    bool lookupUpdate(K key, F slowGetPage);  
    const List &getCacheIn()  { return cacheIn_;  }
    const List &getCacheHot() { return cacheHot_; }
    const List &getCacheOut() { return cacheOut_; }

private:
    double getPartIn()  const { return 0.2; }
    double getPartOut() const { return 0.6; }

    bool fullIn()  const { return (cacheIn_.size()  == sizeCacheIn_);  }
    bool fullHot() const { return (cacheHot_.size() == sizeCacheHot_); }
    bool fullOut() const { return (cacheOut_.size() == sizeCacheOut_); }
    
    bool lookupUpdateIn(K key);
    bool lookupUpdateHot(K key);
    bool lookupUpdateOut(K key);
    
    template <typename F>
    void addToIn(K key, F slowGetPage);
    
    void moveToFront(List &cache, ListIt elt);
    void remove(List &cache, Map &hash, ListIt elt);
    void addToFront(List &cache, Map &hash, K key, T data);

    size_t sizeCacheIn_;
    size_t sizeCacheOut_;
    size_t sizeCacheHot_;
    
    List cacheIn_;
    List cacheOut_;
    List cacheHot_;

    Map hashIn_;
    Map hashHot_;
    Map hashOut_;
};

}  // namespace caches

#include "cache_2q.ipp"