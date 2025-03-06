// Реализация шаблонного класса CacheBelady
// Алгоритм кэширования использует знания о будущих запросах,
// поэтому используется в основном для сравнения с другими алгоритмами

#pragma once

#include <map>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cache {

template <typename CacheItemT, typename KeyT> class CacheBelady2 {
private:
  // Определение типов для работы с кэшем
  using CacheTree =
      std::map<size_t,
               std::pair<KeyT, CacheItemT>>; // Дерево сортированное по времени
                                             // до запроса в будущем
  using CacheTreeIt = typename CacheTree::iterator; // Итератор для дерева
  using CacheMap =
      std::unordered_map<KeyT, CacheTreeIt>; // Хэш-таблица для быстрого доступа
                                             // к элементам кэша

  // Типы для работы с данными о будущих запросах
  using RequestsTree =
      std::map<size_t,
               std::pair<KeyT, std::vector<size_t>>>; // Дерево будущих запросов
  using RequestsTreeIt =
      typename RequestsTree::iterator; // Итератор по дереву будущих запросов
  using RequestMap =
      std::unordered_map<KeyT, RequestsTreeIt>; // Связь между ключом и будущими
                                                // обращениями

public:
  // Конструктор, принимающий размер кэша и последовательность ключей запросов
  CacheBelady2(size_t cacheSize) {
    if (isConstructorArgsValid(cacheSize)) {
      cacheCapacity_ = cacheSize;
    } else {
      throw std::invalid_argument("Invalid cache size");
    }
  }

  CacheBelady2(size_t cacheSize, const std::vector<KeyT> &requestSequence) {
    if (isConstructorArgsValid(cacheSize, requestSequence)) {
      cacheCapacity_ = cacheSize;

      for (size_t i = 0; i < requestSequence.size(); ++i) {
        auto requestMapIt = requestsMap_.find(requestSequence[i]);
        if (requestMapIt == requestsMap_.end()) {
          // Добавляем новый запрос в requestsTree
          auto emplacePair = requestsTree_.emplace(
              i, std::make_pair(requestSequence[i], std::vector<size_t>()));
          if (emplacePair.second) {
            requestsMap_.emplace(requestSequence[i], emplacePair.first);
          } else {
            throw std::invalid_argument("Error emplacing in requestsTree");
          }
        } else {
          // Добавляем время для запроса встречающегося несколько раз
          (requestMapIt->second->second.second).push_back(i);
        }
      }
    } else {
      throw std::invalid_argument("Invalid constructor arguments");
    }
  }

  bool isCacheFull() const { return (cacheTree_.size() == cacheCapacity_); }

  // Основная функция обновления состояния кэша при обращении к элементу
  bool lookupUpdate(KeyT key, CacheItemT (*fetchPage)(KeyT)) {
    if (requestsTree_.size() > 0) {
      if (key != requestsTree_.begin()->second.first) {
        throw std::invalid_argument(
            "Key must be equal to the first element in requestsTree");
      }
    }

    auto cacheMapIt = cacheMap_.find(key);
    if (cacheMapIt != cacheMap_.end()) {
      updateRequestsTree(key);
      return true;
    } else {
      updateRequestsTree(key);
      if (isCacheFull()) {
        if (removeUnwantedItem(key) == key) {
          return false; // Элемент не нужно добавлять, т.к. он больше не будет
                        // запрашиваться
        }
      }
      addItemToCache(key, fetchPage);
      return false;
    }
  }

public:
  bool find(KeyT key) const { return (cacheMap_.find(key) != cacheMap_.end()); }

  const CacheItemT &getItem(KeyT key) const {
    return (cacheMap_.find(key)->second->second.second);
  }

  const CacheTree &getCacheTree() const { return cacheTree_; }

private:
  // Проверка валидности аргументов конструктора
  bool isConstructorArgsValid(size_t cacheSize) const {
    return (cacheSize >= 1);
  }

  bool isConstructorArgsValid(size_t cacheSize,
                              const std::vector<KeyT> &keys) const {
    return (cacheSize >= 1 && !keys.empty());
  }

  void addItemToCache(KeyT newKey, CacheItemT (*fetchPage)(KeyT)) {
    auto requestMapIt = requestsMap_.find(newKey);
    if (requestMapIt == requestsMap_.end()) {
      return;
    }

    size_t distance = requestMapIt->second->first;

    auto emplacePair =
        cacheTree_.emplace(distance, std::make_pair(newKey, fetchPage(newKey)));
    if (emplacePair.second) {
      cacheMap_.emplace(newKey, emplacePair.first);
    } else {
      throw std::invalid_argument("Error emplacing in cacheTree");
    }
  }

  KeyT removeUnwantedItem(KeyT newKey) {
    auto requestMapIt = requestsMap_.find(newKey);
    if (requestMapIt == requestsMap_.end()) {
      return newKey;
    } else {
      KeyT unwantedKey = newKey;
      auto maxDistance = requestMapIt->second->first;

      auto maxRequestDistance = cacheTree_.rbegin()->first;
      if (maxRequestDistance > maxDistance) {
        maxDistance = maxRequestDistance;
        unwantedKey = cacheTree_.rbegin()->second.first;

        auto cacheMapIt = cacheMap_.find(unwantedKey);
        cacheTree_.erase(cacheMapIt->second);
        cacheMap_.erase(cacheMapIt);
      }

      return unwantedKey;
    }
  }

  // Обновление хэш-таблицы будущих запросов
  void updateRequestsTree(KeyT key) {
    auto requestMapIt = requestsMap_.find(key);
    if (requestMapIt == requestsMap_.end()) {
      throw std::invalid_argument(
          "Key must be equal to the first element in requestsMap");
    }

    auto distanceVector = requestMapIt->second->second.second;
    if (distanceVector.size() > 0) {
      // Обновляем расстояние до следующей встречи для запроса
      size_t tmpDistance = distanceVector[0];
      distanceVector.erase(distanceVector.begin());
      auto emplasePair = requestsTree_.emplace(
          tmpDistance, std::make_pair(key, distanceVector));
      if (emplasePair.second == false) {
        throw std::logic_error("emplasePair.second == false");
      } else {
        requestsTree_.erase(requestMapIt->second);
        requestsMap_.erase(requestMapIt);

        requestsMap_.emplace(key, emplasePair.first);
      }

      // Если элемент был в кэше, меняем время доступа к нему на новое
      auto cacheMapIt = cacheMap_.find(key);
      if (cacheMapIt != cacheMap_.end()) {
        auto emplacePair = cacheTree_.emplace(
            tmpDistance,
            std::make_pair(key, cacheMapIt->second->second.second));
        if (emplacePair.second == false) {
          throw std::logic_error("emplacePair.second == false");
        } else {
          cacheTree_.erase(cacheMapIt->second);
          cacheMap_.erase(cacheMapIt);
          cacheMap_.emplace(key, emplacePair.first);
        }
      }
    } else {
      // Удаляем элемент т.к. это последний запрос
      requestsTree_.erase(requestMapIt->second);
      requestsMap_.erase(requestMapIt);

      auto cacheMapIt = cacheMap_.find(key);
      if (cacheMapIt != cacheMap_.end()) {
        cacheTree_.erase(cacheMapIt->second);
        cacheMap_.erase(cacheMapIt);
      }
    }
  }

private:
  size_t cacheCapacity_; // Размер кэша

  CacheTree cacheTree_; // Дерево сортированное по времени до запроса в будущем
  CacheMap cacheMap_;   // Хэш-таблица для доступа к элементам кэша

  RequestsTree requestsTree_; // Дерево будущих запросов сортированное по
                              // времени до запроса
  RequestMap requestsMap_; // Хэш-таблица для доступа к будущим запросам
};

} // namespace cache
