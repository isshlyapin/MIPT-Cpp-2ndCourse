#pragma once

#include <iostream>

#include "cache_belady.hpp"

namespace caches {

template <typename T, typename K>
template <typename F>
bool CacheBelady<T, K>::lookupUpdate(K key, const std::span<K> &keys, F getPage) {
    std::cout << "Start lookupUpdate" << std::endl;
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        std::cout << "Page found in cache" << std::endl;
        return true;
    } else {
        std::cout << "Page not found in cache" << std::endl;
        if (full()) {
            std::cout << "Cache is full" << std::endl;
            K unwanted = getUnwanted(keys, key);
            if (unwanted == key) {
                std::cout << "The page will not be added to cache" << std::endl;
                return false;
            }
            remove(unwanted);
        }
        std::cout << "Add new page in cache" << std::endl;
        addToFront(key, getPage(key));
        return false;
    }    
}

template <typename T, typename K>
K CacheBelady<T, K>::getUnwanted(const std::span<K> &keys, K newKey) {
    std::cout << "Start getUnwanted" << std::endl;

    std::unordered_map<K, size_t> nextUse;
    for (size_t i = 0; i < keys.size(); ++i) {
        if (nextUse.find(keys[i]) == nextUse.end()) {
            nextUse[keys[i]] = i;
        }
    }

    auto itNewKey = nextUse.find(newKey);
    if (itNewKey != nextUse.end()) {
        size_t maxDistance = itNewKey->second;
        K unwanted = newKey;
        
        for (auto elt : cache) {
            auto it = nextUse.find(elt.first);
            if (it == nextUse.end()) {
                return elt.first;
            } else {
                if (it->second > maxDistance) {
                    maxDistance = it->second;
                    unwanted    = elt.first;
                }
            }
        }

        return unwanted;
    }

    return newKey;
}

template <typename T, typename K>
void CacheBelady<T, K>::remove(K key) {
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        // cache.erase(cache.begin());
        cache.erase(elt->second);
        hash.erase(elt);
    }
}

template <typename T, typename K>
void CacheBelady<T, K>::addToFront(K key, T data) {
    cache.emplace_front(key, data);
    hash.emplace(key, cache.begin());
}

} // namespace caches
