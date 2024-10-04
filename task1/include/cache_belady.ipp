#pragma once

namespace caches {

template <typename T, typename K>
template <typename F>
bool CacheBelady<T, K>::lookupUpdate(K key, const std::span<K> &keys, F getPage) {
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        return true;
    } else {
        if (full()) {
            remove(getUnwanted(keys));
        }
        addToFront(key, getPage(key));
        return false;
    }    
}

template <typename T, typename K>
typename CacheBelady<T, K>::ListIt CacheBelady<T, K>::getUnwanted(const std::span<K> &keys) {
    int maxDistance = 0;
    auto unwanted = cache.begin();

    for (auto elt = cache.begin(); elt != cache.end(); ++elt) {
        for (int i{0}; i < keys.size(); ++i) {
            if (keys[i] == elt->first) {
                if (i > maxDistance) {
                    maxDistance = i;
                    unwanted = elt;
                }
                break;
            }
        }
    }

    return unwanted;
}

template <typename T, typename K>
void CacheBelady<T, K>::remove(ListIt elt) {
    hash.erase(elt->first);
    cache.erase(elt);
}

template <typename T, typename K>
void CacheBelady<T, K>::addToFront(K key, T data) {
    cache.emplace_front(key, data);
    hash.emplace(key, cache.begin());
}

} // namespace caches