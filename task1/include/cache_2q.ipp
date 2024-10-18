// cache_impl.hh
#pragma once

#include <stdexcept>

#include "cache_2q.hpp"

namespace caches {

template <typename T, typename K>
Cache2Q<T, K>::Cache2Q(size_t sz) {   
    if (sz < 3) {
        throw std::out_of_range("The value must be at least 3");
    } else if (sz == 3) {
        sizeCacheIn_  = 1;
        sizeCacheOut_ = 1;
        sizeCacheHot_ = 1;
    } else if (sz == 4) {
        sizeCacheIn_  = 1;
        sizeCacheOut_ = 2;
        sizeCacheHot_ = 1;
    } else {
        sizeCacheIn_  = static_cast<size_t>(static_cast<double>(sz) * getPartIn());
        sizeCacheOut_ = static_cast<size_t>(static_cast<double>(sz) * getPartOut());
        sizeCacheHot_ = sz - sizeCacheIn_ - sizeCacheOut_;
    }
}

template <typename T, typename K>
template <typename F>
bool Cache2Q<T, K>::lookupUpdate(K key, F slowGetPage) {
    if (lookupUpdateIn(key) || lookupUpdateHot(key) || lookupUpdateOut(key)) {
        return true;
    } else {
        addToIn(key, slowGetPage);
        return false;
    }
}

template <typename T, typename K>
bool Cache2Q<T, K>::lookupUpdateIn(K key) {
    auto hit = hashIn_.find(key);
    if (hit != hashIn_.end()) {
        moveToFront(cacheIn_, hit->second);
        return true;
    } else {
        return false;
    }
}

template <typename T, typename K>
bool Cache2Q<T, K>::lookupUpdateHot(K key) {
    auto hit = hashHot_.find(key);
    if (hit != hashHot_.end()) {
        moveToFront(cacheHot_, hit->second);
        return true;
    } else {
        return false;
    }
}

template <typename T, typename K>
bool Cache2Q<T, K>::lookupUpdateOut(K key) {
    auto hit = hashOut_.find(key);
    if (hit != hashOut_.end()) {
        if (fullHot()) {
            remove(cacheHot_, hashHot_, std::prev(cacheHot_.end()));
        }
        addToFront(cacheHot_, hashHot_, hit->first, hit->second->second);
        remove(cacheOut_, hashOut_, hit->second);
        return true;
    } else {
        return false;
    }
}

template <typename T, typename K>
template <typename F>
void Cache2Q<T, K>::addToIn(K key, F slowGetPage) {
    if (fullIn()) {
        if (fullOut()) {
            remove(cacheOut_, hashOut_, std::prev(cacheOut_.end()));
        }
        addToFront(cacheOut_, hashOut_, cacheIn_.back().first, cacheIn_.back().second);
        remove(cacheIn_, hashIn_, std::prev(cacheIn_.end()));
    }
    addToFront(cacheIn_, hashIn_, key, slowGetPage(key));
}

template <typename T, typename K>
void Cache2Q<T, K>::moveToFront(List &cache, ListIt elt) {
    if (cache.size() > 1 && elt != cache.begin()) {
        cache.splice(cache.begin(), cache, elt);
    }
}

template <typename T, typename K>
void Cache2Q<T, K>::remove(List &cache, Map &hash, ListIt elt) {
    hash.erase(elt->first);
    cache.erase(elt);
}

template <typename T, typename K>
void Cache2Q<T, K>::addToFront(List &cache, Map &hash, K key, T data) {
    cache.emplace_front(key, data);
    hash.emplace(key, cache.begin());
}

} // namespace caches