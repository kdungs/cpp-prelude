#include "prelude.h"

#include <array>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

auto test_map() -> void {
  using Prelude::map;
  auto expect = std::vector<bool>{false, true, false, true, false};
  auto even = [](int x) { return x % 2 == 0; };
  auto result = map(even, std::vector<int>{1, 2, 3, 4, 5});
  assert(result == expect);
}

auto test_join() -> void {
  using Prelude::join;
  auto expect = std::vector<int>{1, 2, 3, 4};
  auto result = join(std::vector<int>{1, 2}, std::vector<int>{3, 4});
  assert(result == expect);
}

auto test_filter() -> void {
  using Prelude::filter;
  auto expect = std::vector<int>{2, 4};
  auto even = [](int x) { return x % 2 == 0; };
  auto result = filter(even, std::vector<int>{1, 2, 3, 4, 5});
  assert(result == expect);
}

auto test_head() -> void {
  using Prelude::head;
  auto expect = 1;
  auto result = head(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_last() -> void {
  using Prelude::last;
  auto expect = 4;
  auto result = last(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_tail() -> void {
  using Prelude::tail;
  auto expect = std::vector<int>{2, 3, 4};
  auto result = tail(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_init() -> void {
  using Prelude::init;
  auto expect = std::vector<int>{1, 2, 3};
  auto result = init(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_null() -> void {
  using Prelude::null;
  assert(null(std::vector<int>{}));
  assert(!null(std::vector<int>{1}));
}

auto test_length() -> void {
  using Prelude::length;
  assert(length(std::vector<int>{}) == 0);
  assert(length(std::vector<int>{1, 2, 3, 4}) == 4);
}

auto test_at() -> void {
  using Prelude::at;
  assert(at(std::vector<int>{1, 2, 3, 4}, 2) == 3);
}

auto test_reverse() -> void {
  using Prelude::reverse;
  auto expect = std::vector<int>{4, 3, 2, 1};
  auto result = reverse(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_foldl() -> void {
  using Prelude::foldl;
  auto expect = 10;
  auto result = foldl([](int acc, int x) { return acc + x; }, 0,
                      std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_foldl1() -> void {
  using Prelude::foldl1;
  auto expect = 10;
  auto result = foldl1([](int acc, int x) { return acc + x; },
                       std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_foldr() -> void {
  using Prelude::foldr;
  auto expect = 10;
  auto result = foldr([](int x, int acc) { return x + acc; }, 0,
                      std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_foldr1() -> void {
  using Prelude::foldr1;
  auto expect = 10;
  auto result = foldr1([](int x, int acc) { return x + acc; },
                       std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_and_() -> void {
  using Prelude::and_;
  assert(and_(std::vector<bool>{true, true, true, true}) == true);
  assert(and_(std::vector<bool>{true, true, false, true}) == false);
}

auto test_or_() -> void {
  using Prelude::or_;
  assert(or_(std::vector<bool>{false, false, false, false}) == false);
  assert(or_(std::vector<bool>{false, true, false, true}) == true);
}

auto test_any() -> void {
  using Prelude::any;
  assert(any([](int x) { return x > 3; }, std::vector<int>{1, 2, 3, 4}) ==
         true);
  assert(any([](int x) { return x > 5; }, std::vector<int>{1, 2, 3, 4}) ==
         false);
}

auto test_all() -> void {
  using Prelude::all;
  assert(all([](int x) { return x > 3; }, std::vector<int>{1, 2, 3, 4}) ==
         false);
  assert(all([](int x) { return x < 5; }, std::vector<int>{1, 2, 3, 4}) ==
         true);
}

auto test_sum() -> void {
  using Prelude::sum;
  auto expect = 10;
  auto result = sum(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_product() -> void {
  using Prelude::product;
  auto expect = 24;
  auto result = product(std::vector<int>{1, 2, 3, 4});
  assert(result == expect);
}

auto test_concat() -> void {
  using Prelude::concat;
  auto expect = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto result = concat(
      std::array<std::vector<int>, 3>{{{1, 2, 3}, {4, 5}, {6, 7, 8, 9}}});
  assert(result == expect);
}

auto test_concatMap() -> void {
  using Prelude::concatMap;
  auto expect = std::vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3};
  auto result = concatMap([](int x) {
    return std::vector<int>{x, x, x};
  }, std::list<int>{1, 2, 3});
  assert(result == expect);
}

auto test_maximum() -> void {
  using Prelude::maximum;
  auto expect = 23;
  auto result = maximum(std::vector<int>{1, 2, 3, 23, 4, 5});
  assert(result == expect);
}

auto test_minimum() -> void {
  using Prelude::minimum;
  auto expect = -23;
  auto result = minimum(std::vector<int>{1, 2, 3, 4, -23, 5});
  assert(result == expect);
}


int main() {
  // List operations
  test_map();
  test_join();
  test_filter();
  test_head();
  test_last();
  test_tail();
  test_init();
  test_null();
  test_at();
  test_reverse();
  // Reducing lists (folds)
  test_foldl();
  test_foldl1();
  test_foldr();
  test_foldr1();
  // Special folds
  test_and_();
  test_or_();
  test_any();
  test_all();
  test_sum();
  test_product();
  test_concat();
  test_concatMap();
  test_maximum();
  test_minimum();
}
