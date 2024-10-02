#pragma once

#include <iostream>
#include <cstddef>
#include <vector>
#include <cassert>

#include "cache.hh"

// slow get page imitation
static int slow_get_page_int(int key) { return key; }

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
int checkCache(size_t szCache, size_t amountPages, std::vector<K> &keys, F getPage) {
    caches::Cache<int> cache(szCache);

    int hits{0};
    for (size_t i{0}; i < amountPages; ++i) {
        if (cache.lookupUpdate(keys[i], getPage)) {
            hits++;
        }
    }

    return hits;
}