#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>

namespace Prelude {

#define Container               \
  template <typename, typename> \
  class
#define Function typename
#define Predicate typename
#define Type typename

/*
 * List operations
 */

// map :: (a -> b) -> [a] -> [b]
template <Function FN, Container CN, Type A,
          Type B = typename std::result_of<FN(A)>::type,
          typename AllocA = std::allocator<A>,
          typename AllocB = std::allocator<B>>
auto map(const FN& f, const CN<A, AllocA>& c) -> CN<B, AllocB> {
  auto res = CN<B, AllocB>{};
  res.reserve(c.size());
  std::transform(std::begin(c), std::end(c), std::back_inserter(res), f);
  return res;
}

// (++) :: [a] -> [a] -> [a]

// filter :: (a -> Bool) -> [a] -> [a]
template <Predicate PR, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto filter(const PR& p, const CN<A, AllocA>& c) -> CN<A, AllocA> {
  auto res = CN<A, AllocA>{};
  res.reserve(c.size());
  std::copy_if(std::begin(c), std::end(c), std::back_inserter(res), p);
  res.shrink_to_fit();
  return res;
}

// head :: [a] -> a
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto head(const CN<A, AllocA>& c) -> A {
  assert(c.size() && "Container can't be empty.");
  return c.front();
}

// last :: [a] -> a
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto last(const CN<A, AllocA>& c) -> A {
  assert(c.size() && "Container can't be empty.");
  return c.back();
}

// tail :: [a] -> [a]
// init :: [a] -> [a]
// null :: [a] -> Bool
// length :: [a] -> Int
// (!!) :: [a] -> Int -> a
// reverse :: [a] -> [a]
}
