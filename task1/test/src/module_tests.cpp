#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "cache_belady2.hpp" // подключаем наш класс

// Вспомогательная функция для создания страниц
int fetchPage(int key) { return key * 10 - 666; }

// Тесты на проверку работы метода isCacheFull
TEST(CacheBelady2Test, IsCacheFull) {
  std::vector<int> requestSequence = {1, 2, 3, 1, 2, 3};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  EXPECT_FALSE(cache.isCacheFull());

  cache.lookupUpdate(1, fetchPage);
  EXPECT_FALSE(cache.isCacheFull());

  cache.lookupUpdate(2, fetchPage);
  cache.lookupUpdate(3, fetchPage);

  EXPECT_TRUE(cache.isCacheFull());
}

// Тесты метода lookupUpdate для поиска и обновления
TEST(CacheBelady2Test, LookupUpdateKeyFoundInCache) {
  std::vector<int> requestSequence = {1, 1, 3, 4, 1};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  cache.lookupUpdate(1, fetchPage);

  EXPECT_TRUE(cache.lookupUpdate(1, fetchPage));
}

TEST(CacheBelady2Test, LookupUpdateKeyNotFoundInCache) {
  std::vector<int> requestSequence = {1, 2, 3, 4};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  EXPECT_FALSE(cache.lookupUpdate(1, fetchPage));
  EXPECT_FALSE(cache.lookupUpdate(2, fetchPage));
  EXPECT_FALSE(cache.lookupUpdate(3, fetchPage));
}

// Тесты добавления нового элемента в кэш
TEST(CacheBelady2Test, AddNewItemToCache) {
  std::vector<int> requestSequence = {1, 2, 3, 3, 2, 1};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  cache.lookupUpdate(1, fetchPage);
  cache.lookupUpdate(2, fetchPage);
  cache.lookupUpdate(3, fetchPage);

  EXPECT_TRUE(cache.isCacheFull());              // Кэш полный
  EXPECT_TRUE(cache.lookupUpdate(3, fetchPage)); // Элемент найден
}

// Тесты удаления нежелательного элемента
TEST(CacheBelady2Test, RemoveUnwantedItem) {
  std::vector<int> requestSequence = {1, 2, 3, 4, 5, 1, 4, 2, 3, 4, 5};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  cache.lookupUpdate(1, fetchPage);
  cache.lookupUpdate(2, fetchPage);
  cache.lookupUpdate(3, fetchPage);
  cache.lookupUpdate(4, fetchPage);

  EXPECT_FALSE(cache.find(3));
}

// Тесты работы с запросами (RequestsTree)
TEST(CacheBelady2Test, UpdateRequestsTree) {
  std::vector<int> requestSequence = {1, 2, 3, 1, 4, 2, 3, 5, 5, 4};
  cache::CacheBelady2<int, int> cache(3, requestSequence);

  cache.lookupUpdate(1, fetchPage);
  EXPECT_THROW(cache.lookupUpdate(1, fetchPage), std::invalid_argument);
}
