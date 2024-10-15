#pragma once

#include <list>
#include <unordered_map>
#include <cstddef>
#include <span>
#include <stdexcept>

namespace caches {
    
template <typename T, typename K = int>
class CacheBelady {
private:
    using List   = typename std::list<std::pair<K, T>>;
    using ListIt = typename List::iterator;
    using Map    = typename std::unordered_map<K, ListIt>;

public:
    CacheBelady(size_t sz) {
        if (sz < 1) {
            throw std::out_of_range("The value must be at least 1");
        } else {
            sizeCache = sz;
        }
    }
    
    template <typename F>
    bool lookupUpdate(K key, const std::span<K> &keys, F getPage);
    const List &getCache()  { return cache; }

private:
    bool full() const { return (cache.size()  == sizeCache); }
    
    void remove(K key);
    void addToFront(K key, T data);

    K getUnwanted(const std::span<K> &keys, K newKey);

    size_t sizeCache;
    
    List cache;

    Map hash;
};

} // namespace caches

#include "cache_belady.ipp"