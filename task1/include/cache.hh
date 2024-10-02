// cache.hh
#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <cstddef>
#include <vector>

// #include <spdlog/spdlog.h>
// #include <spdlog/sinks/stdout_color_sinks.h>

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
    const List &getCacheIn()  { return cacheIn_;  };
    const List &getCacheHot() { return cacheHot_; };
    const List &getCacheOut() { return cacheOut_; };

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


    // std::shared_ptr<spdlog::logger> logger;

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

template <typename T, typename K = int>
class CacheBelady {
private:
    using List   = typename std::list<std::pair<K, T>>;
    using ListIt = typename List::iterator;
    using Map    = typename std::unordered_map<K, ListIt>;

public:
    CacheBelady(size_t sz) : sizeCache(sz) {}
    
    template <typename F>
    bool lookupUpdate(K key, std::vector<K> &keys, F getPage);  
    const List &getCache()  { return cache;  };

private:
    bool full()  const { return (cache.size()  == sizeCache);  }
    
    void moveToFront(ListIt elt);
    void remove(ListIt elt);
    void addToFront(K key, T data);

    ListIt getUnwanted(std::vector<K> &keys) {
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

    size_t sizeCache;
    
    List cache;

    Map hash;
};

template <typename T, typename K>
template <typename F>
bool CacheBelady<T, K>::lookupUpdate(K key, std::vector<K> &keys, F getPage) {
    auto elt = hash.find(key);
    if (elt != hash.end()) {
        moveToFront(elt->second);
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
void CacheBelady<T, K>::moveToFront(ListIt elt) {
    if (cache.size() > 1 && elt != cache.begin()) {
        cache.splice(cache.begin(), cache, elt);
    }
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


// template <typename T, typename K>
// ListIt CacheBelady<T, K>::getUnwanted(std::vector<K> &keys) {
//     int maxDistance = 0;
//     auto unwanted = cache.begin();

//     for (auto elt = cache.begin(); elt != cache.end(); ++elt) {
//         for (int i{0}; i < keys.size(); ++i) {
//             if (keys[i] == elt->first) {
//                 if (i > maxDistance) {
//                     maxDistance = i;
//                     unwanted = elt;
//                 }
//                 break;
//             }
//         }
//     }

//     return unwanted;
// }

#include "cache_impl.hh"

}  // namespace caches
