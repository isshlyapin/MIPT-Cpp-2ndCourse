#pragma once

#include <cstdio>
#include <iostream>
#include <cstddef>
#include <ostream>
#include <vector>
#include <cassert>
#include <span>

#include "cache_2q.hpp"
#include "cache_belady.hpp"
#include "cache_belady2.hpp"

static int getPage(int key) {
    return key*3 - 666;
}

template <typename K>
void getInputData(size_t &szCache, size_t &amountPages, std::vector<K> &keys) {
    std::cout << "> ";

    std::cin >> szCache >> amountPages;
    assert(std::cin.good());
    std::cout << "\nszCache = " << szCache << "; amountPages = " << amountPages << std::endl;    
    
    /*std::cout << "[";*/
    for (size_t i = 0; i < amountPages; ++i) {
        K key = 0;
        std::cin >> key; 
        assert(std::cin.good());
        /*std::cout << key << " ";*/
        
        keys.push_back(key);
    }
    /*std::cout << "]" << std::endl;*/
}

template <typename K>
int checkCache2Q(size_t szCache, size_t amountPages, std::vector<K> &keys) {
    caches::Cache2Q<int> cache(szCache);

    int hits{0};
    for (size_t i{0}; i < amountPages; ++i) {
        // std::cout << std::endl << "lookupUpdate page: " << i << " | " << "key: " << keys[i] << std::endl;
        if (cache.lookupUpdate(keys[i], getPage)) {
            hits++;
        }
    }

    return hits;
}

template <typename K>
int checkCacheBelady(size_t szCache, size_t amountPages, std::vector<K> &keys) {
    caches::CacheBelady<int> cache(szCache);

    int hits = 0;
    for (size_t i = 0; i < amountPages; ++i) {
        if (cache.lookupUpdate(keys[i], std::span<K>(keys).subspan(i + 1), getPage)) {
            hits++;
        }
    }

    return hits;
}

template <typename K>
int checkCacheBelady2(size_t szCache, std::vector<K> &keys) {
    caches::CacheBelady2<int, int> cache{szCache, keys};

    int hits = 0;
    for (size_t i = 0; i < keys.size(); ++i) {
        if (cache.lookupUpdate(keys[i], getPage)) {
            hits++;
        }
    }

    return hits;
}
