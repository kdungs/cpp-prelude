#include "prelude.h"

#include <cassert>
#include <iostream>
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

int main() {
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
}
