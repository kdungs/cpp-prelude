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

// -----------------
//  List operations 
// -----------------

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
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto join(const CN<A, AllocA>& left, const CN<A, AllocA>& right)
    -> CN<A, AllocA> {
  auto res = CN<A, AllocA>{left};
  res.insert(std::end(res), std::begin(right), std::end(right));
  return res;
}

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
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto tail(const CN<A, AllocA>& c) -> CN<A, AllocA> {
  assert(c.size() && "Container can't be empty.");
  auto res = CN<A, AllocA>{std::begin(c) + 1, std::end(c)};
  return res;
}

// init :: [a] -> [a]
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto init(const CN<A, AllocA>& c) -> CN<A, AllocA> {
  assert(c.size() && "Container can't be empty.");
  auto res = CN<A, AllocA>{std::begin(c), std::end(c) - 1};
  return res;
}

// null :: [a] -> Bool
template <typename _Container>
auto null(const _Container& c) -> bool {
  return c.empty();
}

// length :: [a] -> Int
template <typename _Container>
auto length(const _Container& c) -> std::size_t {
  return c.size();
}

// (!!) :: [a] -> Int -> a
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto at(const CN<A, AllocA>& c, std::size_t pos) -> A {
  assert(pos < c.size() && "Position has to be within size of Container.");
  return c.at(pos);
}

// reverse :: [a] -> [a]
template <Container CN, Type A, typename AllocA = std::allocator<A>>
auto reverse(const CN<A, AllocA>& c) -> CN<A, AllocA> {
  auto res = CN<A, AllocA>{c};
  std::reverse(std::begin(res), std::end(res));
  return res;
}


// ------------------------
//  Reducing lists (folds) 
// ------------------------

// foldl :: (b -> a -> b) -> b -> [a] -> b
// foldl1 :: (a -> a -> a) -> [a] -> a
// foldr :: (a -> b -> b) -> b -> [a] -> b
// foldr1 :: (a -> a -> a) -> [a] -> a

}
