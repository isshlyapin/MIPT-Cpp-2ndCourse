#pragma once

#include <cstdio>
#include <iostream>
#include <cstddef>
#include <vector>
#include <cassert>
#include <span>

#include "cache_2q.hpp"
#include "cache_belady.hpp"

template <typename K>
void getInputData(size_t &szCache, size_t &amountPages, std::vector<K> &keys) {
    std::cout << "> ";

    std::cin >> szCache >> amountPages;
    assert(std::cin.good());

    for (size_t i{0}; i < amountPages; ++i) {
        K key;
        std::cin >> key; 
        assert(std::cin.good());
        
        keys.push_back(key);
    }
}

template <typename K, typename F>
int checkCache2Q(size_t szCache, size_t amountPages, std::vector<K> &keys, F getPage) {
    caches::Cache2Q<int> cache(szCache);

    int hits{0};
    for (size_t i{0}; i < amountPages; ++i) {
        std::cout << std::endl << "lookupUpdate page: " << i << " | " << "key: " << keys[i] << std::endl;
        if (cache.lookupUpdate(keys[i], getPage)) {
            hits++;
        }
    }

    return hits;
}

template <typename K, typename F>
int checkCacheBelady(size_t szCache, size_t amountPages, std::vector<K> &keys, F getPage) {
    caches::CacheBelady<int> cache(szCache);

    int hits{0};
    for (size_t i{0}; i < amountPages; ++i) {
        std::cout << std::endl << "lookupUpdate page: " << i << " | " << "key: " << keys[i] << std::endl;
        if (cache.lookupUpdate(keys[i], std::span<K>(keys).subspan(i + 1), getPage)) {
            hits++;
        }
    }

    return hits;
}
