#include "prelude.h"

#include <array>
#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

auto test_not_() -> void {
  using Prelude::not_;
  auto even = [](int x) { return x % 2 == 0; };
  auto odd = not_<int>(even);
  assert(odd(3) == true);
  assert(odd(2) == false);
}

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

auto test_take() -> void {
  using Prelude::take;
  auto expect = std::vector<int>{1, 2, 3, 4};
  auto result = take(4, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(result == expect);
  // also check case for n > size
  result = take(100, expect);
  assert(result == expect && "Also has to work for n > size!");
}

auto test_drop() -> void {
  using Prelude::drop;
  auto expect = std::vector<int>{5, 6, 7, 8};
  auto result = drop(4, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(result == expect);
  // also check case for n > size
  result = drop(100, std::vector<int>{1, 2, 3, 4});
  expect = std::vector<int>{};
  assert(result == expect && "Also has to work for n > size!");
}

auto test_splitAt() -> void {
  using Prelude::splitAt;
  auto expectL = std::vector<int>{1, 2, 3, 4};
  auto expectR = std::vector<int>{5, 6, 7, 8};
  std::vector<int> resultL, resultR;
  std::tie(resultL, resultR) =
      splitAt(4, std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(resultL == expectL);
  assert(resultR == expectR);
  // empty first half
  expectL = std::vector<int>{};
  expectR = std::vector<int>{1, 2, 3, 4};
  std::tie(resultL, resultR) = splitAt(0, std::vector<int>{1, 2, 3, 4});
  assert(resultL == expectL);
  assert(resultR == expectR);
  // empty second half
  expectL = std::vector<int>{1, 2, 3, 4};
  expectR = std::vector<int>{};
  std::tie(resultL, resultR) = splitAt(10, std::vector<int>{1, 2, 3, 4});
  assert(resultL == expectL);
  assert(resultR == expectR);
}

auto test_takeWhile() -> void {
  using Prelude::takeWhile;
  auto expect = std::vector<int>{1, 2, 3, 4};
  auto result = takeWhile([](int x) { return x < 5; },
                          std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(result == expect);
}

auto test_dropWhile() -> void {
  using Prelude::dropWhile;
  auto expect = std::vector<int>{5, 6, 7, 8};
  auto result = dropWhile([](int x) { return x < 5; },
                          std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(result == expect);
}

auto test_span() -> void {
  using Prelude::span;
  auto expectL = std::vector<int>{1, 2, 3, 4};
  auto expectR = std::vector<int>{5, 6, 7, 8};
  std::vector<int> resultL, resultR;
  std::tie(resultL, resultR) = span([](int x) { return x < 5; },
                                    std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(resultL == expectL);
  assert(resultR == expectR);
}

auto test_break_() -> void {
  using Prelude::break_;
  auto expectL = std::vector<int>{1, 2, 3, 4};
  auto expectR = std::vector<int>{5, 6, 7, 8};
  std::vector<int> resultL, resultR;
  std::tie(resultL, resultR) = break_([](int x) { return x >= 5; },
                                      std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
  assert(resultL == expectL);
  assert(resultR == expectR);
}

auto test_zip() -> void {
  using Prelude::zip;
  auto expect = std::vector<std::tuple<int, bool>>{std::make_tuple(1, true),
                                                   std::make_tuple(2, false),
                                                   std::make_tuple(3, true)};
  auto result =
      zip(std::vector<int>{1, 2, 3}, std::list<bool>{true, false, true});
  assert(result == expect);
}

auto test_zip3() -> void {
  using Prelude::zip3;
  auto expect = std::vector<std::tuple<int, bool, char>>{
      std::make_tuple(1, true, 'a'), std::make_tuple(2, false, 'b'),
      std::make_tuple(3, true, 'm')};
  auto result =
      zip3(std::vector<int>{1, 2, 3}, std::list<bool>{true, false, true},
           std::vector<char>{'a', 'b', 'm'});
  assert(result == expect);
}

auto test_zipWith() -> void {
  using Prelude::zipWith;
  auto expect = std::vector<int>{1, 0, 3, 0, 5, 0};
  auto result = zipWith([](int x, bool y) { return y ? x : 0; },
                        std::vector<int>{1, 2, 3, 4, 5, 6},
                        std::list<bool>{true, false, true, false, true, false});
  assert(result == expect);
}

auto test_zipWith3() -> void {
  using Prelude::zipWith3;
  auto expect = std::vector<std::string>{"aaa", "", "ccccc"};
  auto result =
      zipWith3([](int x, bool y, char z) { return y ? std::string(x, z) : ""; },
               std::vector<int>{3, 4, 5}, std::list<bool>{true, false, true},
               std::list<char>{'a', 'b', 'c'});
  assert(result == expect);
}

auto test_unzip() -> void {
  using Prelude::unzip;
  auto expectL = std::vector<int>{1, 2, 3};
  auto expectR = std::vector<bool>{true, false, true};
  std::vector<int> resultL;
  std::vector<bool> resultR;
  std::tie(resultL, resultR) = unzip(std::vector<std::tuple<int, bool>>{
      std::make_tuple(1, true), std::make_tuple(2, false),
      std::make_tuple(3, true)});
  assert(resultL == expectL);
  assert(resultR == expectR);
}

auto test_unzip3() -> void {
  using Prelude::unzip3;
  auto expectL = std::vector<int>{1, 2, 3};
  auto expectM = std::vector<char>{'a', 'b', 'c'};
  auto expectR = std::vector<bool>{true, false, true};
  std::vector<int> resultL;
  std::vector<char> resultM;
  std::vector<bool> resultR;
  std::tie(resultL, resultM, resultR) =
      unzip3(std::vector<std::tuple<int, char, bool>>{
          std::make_tuple(1, 'a', true), std::make_tuple(2, 'b', false),
          std::make_tuple(3, 'c', true)});
  assert(resultL == expectL);
  assert(resultM == expectM);
  assert(resultR == expectR);
}

int main() {
  test_not_();
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
  // Sublists
  test_take();
  test_drop();
  test_splitAt();
  test_takeWhile();
  test_dropWhile();
  test_span();
  test_break_();
  // Zipping and unzipping lists
  test_zip();
  test_zip3();
  test_zipWith();
  test_zipWith3();
  test_unzip();
  test_unzip3();

  std::cout << "Looking good!\n";
}
