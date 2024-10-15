#pragma once

#include <cstddef>
namespace caches {

template <typename T, typename K>
template <typename F>
bool CacheBelady<T, K>::lookupUpdate(K key, const std::span<K> &keys, F getPage) {
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        return true;
    } else {
        if (full()) {
            K unwanted = getUnwanted(keys, key);
            if (unwanted == key) {
                return false;
            }
            remove(unwanted);
        }
        addToFront(key, getPage(key));
        return false;
    }    
}

template <typename T, typename K>
K CacheBelady<T, K>::getUnwanted(const std::span<K> &keys, K newKey) {
    size_t maxDistance = 0;
    bool found = false;
    K unwanted;

    for (size_t i = 0; i < keys.size(); ++i) {
        if (keys[i] == newKey) {
            maxDistance = i;
            unwanted = newKey;
            found = true;
            break;
        }
    }

    if (!found) {
        return newKey;
    }

    for (auto elt = cache.begin(); elt != cache.end(); ++elt) {
        found = false;
        for (size_t i = 0; i < keys.size(); ++i) {
            if (keys[i] == elt->first) {
                if (i > maxDistance) {
                    maxDistance = i;
                    unwanted = elt->first;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            unwanted = elt->first;
            break;
        }
    }

    return unwanted;
}

template <typename T, typename K>
void CacheBelady<T, K>::remove(K key) {
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        cache.erase(elt->second);
        hash.erase(elt->first);
    }
}

template <typename T, typename K>
void CacheBelady<T, K>::addToFront(K key, T data) {
    cache.emplace_front(key, data);
    hash.emplace(key, cache.begin());
}

} // namespace caches