// cache_impl.hh
#pragma once

template <typename T, typename K>
Cache2Q<T, K>::Cache2Q(size_t sz) {
    // logger = spdlog::stdout_color_mt("console");
    // logger->set_pattern("[%^%l%$] %v");

    // #ifdef MYLOG_DEBUG
    //     spdlog::set_level(spdlog::level::debug);
    // #else
    //     spdlog::set_level(spdlog::level::off);
    // #endif
    
    if (sz < 3) {
        throw std::out_of_range("The value must be at least 3");
    } else if (sz == 3) {
        sizeCache2QIn_  = 1;
        sizeCache2QOut_ = 1;
        sizeCache2QHot_ = 1;
    } else if (sz == 4) {
        sizeCache2QIn_  = 1;
        sizeCache2QOut_ = 2;
        sizeCache2QHot_ = 1;
    } else {
        sizeCache2QIn_  = sz * getPartIn();
        sizeCache2QOut_ = sz * getPartOut();
        sizeCache2QHot_ = sz - sizeCache2QIn_ - sizeCache2QOut_;
    }
}

template <typename T, typename K>
template <typename F>
bool Cache2Q<T, K>::lookupUpdate(K key, F slowGetPage) {
    // logger->debug("Started lookupUpdate");
    if (lookupUpdateIn(key) || lookupUpdateHot(key) || lookupUpdateOut(key)) {
        return true;
    } else {
        addToIn(key, slowGetPage);
        return false;
    }
}

template <typename T, typename K>
bool Cache2Q<T, K>::lookupUpdateIn(K key) {
    // logger->debug("Started lookupUpdateIn");
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
    // logger->debug("Started lookupUpdateHot");
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
    // logger->debug("Started lookupUpdateOut");
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
    // logger->debug("Started addToIn");
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
    // logger->debug("Started moveToFront");
    if (cache.size() > 1 && elt != cache.begin()) {
        cache.splice(cache.begin(), cache, elt);
    }
}

template <typename T, typename K>
void Cache2Q<T, K>::remove(List &cache, Map &hash, ListIt elt) {
    // logger->debug("Started remove");
    hash.erase(elt->first);
    cache.erase(elt);
}

template <typename T, typename K>
void Cache2Q<T, K>::addToFront(List &cache, Map &hash, K key, T data) {
    // logger->debug("Started addToFront");
    cache.emplace_front(key, data);
    hash.emplace(key, cache.begin());
}