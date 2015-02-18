#include "prelude.h"

#include <cassert>
#include <iostream>
#include <vector>

auto test_map() -> void {
  using Prelude::map;
  auto expected = std::vector<bool>{false, true, false, true, false};
  auto even = [](int x) { return x % 2 == 0; };
  auto result = map(even, std::vector<int>{1, 2, 3, 4, 5});
  assert(result == expected);
}

auto test_filter() -> void {
  using Prelude::filter;
  auto expected = std::vector<int>{2, 4};
  auto even = [](int x) { return x % 2 == 0; };
  auto result = filter(even, std::vector<int>{1, 2, 3, 4, 5});
  assert(result == expected);
}

auto test_head() -> void {
  using Prelude::head;
  assert(head(std::vector<int>{1, 2, 3, 4}) == 1);
}

auto test_last() -> void {
  using Prelude::last;
  assert(last(std::vector<int>{1, 2, 3, 4}) == 4);
}

int main() {
  test_map();
  test_filter();
  test_head();
  test_last();
}
