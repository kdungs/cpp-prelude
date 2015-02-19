#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <numeric>

namespace Prelude {

#define Container               \
  template <typename, typename> \
  class
#define Function typename
#define Predicate typename
#define Type typename
#define Number typename
#define Ordinal typename

// not :: (a -> Bool) -> (a -> Bool)
template <Type A>  // needs to be passed explicitly for the moment
auto not_(const std::function<bool(A)>& p) -> std::function<bool(A)> {
  return [&](A x) { return !p(x); };
}

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
template <Function FN, Type B, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto foldl(const FN& f, B&& acc, const CN<A, AllocA>& c) -> B {
  return std::accumulate(std::begin(c), std::end(c), std::forward<B>(acc), f);
}

// foldl1 :: (a -> a -> a) -> [a] -> a
template <Function FN, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto foldl1(const FN& f, const CN<A, AllocA>& c) -> A {
  assert(c.size() && "Container can't be empty.");
  return std::accumulate(std::begin(c) + 1, std::end(c), c.front(), f);
}

// foldr :: (a -> b -> b) -> b -> [a] -> b
template <Function FN, Type B, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto foldr(const FN& f, B&& acc, const CN<A, AllocA>& c) -> B {
  // One way to do this is assuming a BidirIt and iterating the Container back
  // to front. The following is a more general approach that probably entails a
  // lot of copies. To be benchmarked!
  if (null(c)) {
    return std::forward<B>(acc);
  }
  return f(head(c),
           foldr<FN, B, CN, A, AllocA>(f, std::forward<B>(acc), tail(c)));
}

// foldr1 :: (a -> a -> a) -> [a] -> a
template <Function FN, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto foldr1(const FN& f, const CN<A, AllocA>& c) -> A {
  assert(c.size() && "Container can't be empty.");
  if (null(tail(c))) {
    return head(c);
  }
  return f(head(c), foldr1<FN, CN, A, AllocA>(f, tail(c)));
}

// ---------------
//  Special folds
// ---------------

// and :: [Bool] -> Bool
template <Container CN, typename Alloc = std::allocator<bool>>
auto and_(const CN<bool, Alloc>& c) -> bool {
  return std::all_of(std::begin(c), std::end(c), [](bool x) { return x; });
}

// or :: [Bool] -> Bool
template <Container CN, typename Alloc = std::allocator<bool>>
auto or_(const CN<bool, Alloc>& c) -> bool {
  return std::any_of(std::begin(c), std::end(c), [](bool x) { return x; });
}

// any :: (a -> Bool) -> [a] -> Bool
template <Function FN, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto any(const FN& f, const CN<A, AllocA>& c) -> bool {
  return std::any_of(std::begin(c), std::end(c), f);
}

// all :: (a -> Bool) -> [a] -> Bool
template <Function FN, Container CN, Type A,
          typename AllocA = std::allocator<A>>
auto all(const FN& f, const CN<A, AllocA>& c) -> bool {
  return std::all_of(std::begin(c), std::end(c), f);
}

// sum :: Num a => [a] -> a
template <Container CN, Number A, typename AllocA = std::allocator<A>>
auto sum(const CN<A, AllocA>& c) -> A {
  return foldl([](const A& acc, const A& x) { return acc + x; }, A{0}, c);
}

// product :: Num a => [a] -> a
template <Container CN, Number A, typename AllocA = std::allocator<A>>
auto product(const CN<A, AllocA>& c) -> A {
  return foldl([](const A& acc, const A& x) { return acc * x; }, A{1}, c);
}

// concat :: [[a]] -> [a]
template <typename _Container, typename Inner = typename _Container::value_type>
auto concat(const _Container& c) -> Inner {
  auto res = Inner{};
  for (const auto _c : c) {
    res.insert(std::end(res), std::begin(_c), std::end(_c));
  }
  return res;
}

// concatMap :: (a -> [b]) -> [a] -> [b]
template <Function FN, Container CN, Type A,
          typename AllocA = std::allocator<A>,
          typename Inner = typename std::result_of<FN(A)>::type,
          typename AllocInner = std::allocator<Inner>>
auto concatMap(const FN& f, const CN<A, AllocA>& c) -> Inner {
  return concat<CN<Inner, AllocInner>, Inner>(
      map<FN, CN, A, Inner, AllocA, AllocInner>(f, c));
}

// maximum :: Ord a => [a] -> a
template <typename _Container, Ordinal A = typename _Container::value_type>
auto maximum(const _Container& c) -> A {
  return *std::max_element(std::begin(c), std::end(c));
}
// minimum :: Ord a => [a] -> a
template <typename _Container, Ordinal A = typename _Container::value_type>
auto minimum(const _Container& c) -> A {
  return *std::min_element(std::begin(c), std::end(c));
}

// ----------------
//  Building lists
// ----------------

// scanl :: (b -> a -> b) -> b -> [a] -> [b]
// scanl1 :: (a -> a -> a) -> [a] -> [a]
// scanr :: (a -> b -> b) -> b -> [a] -> [b]
// scanr1 :: (a -> a -> a) -> [a] -> [a]

// ----------------
//  Infinite lists
// ----------------
//
// Without lazy evaluation, there is not really any way to produce infinite
// lists. Maybe I'll implement these functions with an additional size
// parameter.

// ----------
//  Sublists
// ----------

// take :: Int -> [a] -> [a]
template <typename _Container>
auto take(std::size_t n, const _Container& c) -> _Container {
  return _Container{std::begin(c),
                    n > c.size() ? std::end(c) : std::begin(c) + n};
}

// drop :: Int -> [a] -> [a]
template <typename _Container>
auto drop(std::size_t n, const _Container& c) -> _Container {
  return _Container{n > c.size() ? std::end(c) : std::begin(c) + n,
                    std::end(c)};
}

// splitAt :: Int -> [a] -> ([a], [a])
template <typename _Container>
auto splitAt(std::size_t n, const _Container& c)
    -> std::tuple<_Container, _Container> {
  return std::make_tuple(take(n, c), drop(n, c));
}

// takeWhile :: (a -> Bool) -> [a] -> [a]
template <Predicate PR, typename _Container>
auto takeWhile(const PR& p, const _Container& c) -> _Container {
  return _Container(std::begin(c),
                    std::partition_point(std::begin(c), std::end(c), p));
}

// dropWhile :: (a -> Bool) -> [a] -> [a]
template <Predicate PR, typename _Container>
auto dropWhile(const PR& p, const _Container& c) -> _Container {
  return _Container(std::partition_point(std::begin(c), std::end(c), p),
                    std::end(c));
}

// span :: (a -> Bool) -> [a] -> ([a], [a])
template <Predicate PR, typename _Container>
auto span(const PR& p, const _Container& c)
    -> std::tuple<_Container, _Container> {
  auto pp = std::partition_point(std::begin(c), std::end(c), p);
  return std::make_tuple(_Container{std::begin(c), pp},
                         _Container{pp, std::end(c)});
}

// break :: (a -> Bool) -> [a] -> ([a], [a])
template <Predicate PR, typename _Container>
auto break_(const PR& p, const _Container& c)
    -> std::tuple<_Container, _Container> {
  return span(not_<typename _Container::value_type>(p), c);
}

// -----------------
//  Searching lists
// -----------------

// elem :: Eq a => a -> [a] -> Bool
// notElem :: Eq a => a -> [a] -> Bool
// lookup :: Eq a => a -> [(a, b)] -> Maybe b

// -----------------------------
//  Zipping and unzipping lists
// -----------------------------

// zip :: [a] -> [b] -> [(a, b)]
template <Container CA, Type A, typename AllocA = std::allocator<A>,
          Container CB, Type B, typename AllocB = std::allocator<B>,
          Container CRES = CA, typename RES = std::tuple<A, B>,
          typename AllocRES = std::allocator<RES>>
auto zip(const CA<A, AllocA>& left, const CB<B, AllocB>& right)
    -> CRES<RES, AllocRES> {
  auto res = CRES<RES, AllocRES>{};
  auto l = std::begin(left);
  auto r = std::begin(right);
  while (l != std::end(left) && r != std::end(right)) {
    res.emplace_back(*l, *r);
    ++l;
    ++r;
  }
  return res;
}

// zip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
template <Container CA, Type A, typename AllocA = std::allocator<A>,
          Container CB, Type B, typename AllocB = std::allocator<B>,
          Container CC, Type C, typename AllocC = std::allocator<C>,
          Container CRES = CA, typename RES = std::tuple<A, B, C>,
          typename AllocRES = std::allocator<RES>>
auto zip3(const CA<A, AllocA>& left, const CB<B, AllocB>& middle,
          const CC<C, AllocC>& right) -> CRES<RES, AllocRES> {
  auto res = CRES<RES, AllocRES>{};
  auto l = std::begin(left);
  auto m = std::begin(middle);
  auto r = std::begin(right);
  while (l != std::end(left) && m != std::end(middle) && r != std::end(right)) {
    res.emplace_back(*l, *m, *r);
    ++l;
    ++m;
    ++r;
  }
  return res;
}

// zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
template <Function FN, Container CA, Type A,
          typename AllocA = std::allocator<A>, Container CB, Type B,
          typename AllocB = std::allocator<B>, Container CC = CA,
          Type C = typename std::result_of<FN(A, B)>::type,
          typename AllocC = std::allocator<C>>
auto zipWith(const FN& f, const CA<A, AllocA>& left, const CB<B, AllocB>& right)
    -> CC<C, AllocC> {
  auto res = CC<C, AllocC>{};
  auto l = std::begin(left);
  auto r = std::begin(right);
  while (l != std::end(left) && r != std::end(right)) {
    res.emplace_back(f(*l, *r));
    ++l;
    ++r;
  }
  return res;
}

// zipWith3 :: (a -> b -> c -> d) -> [a] -> [b] -> [c] -> [d]
template <Function FN, Container CA, Type A,
          typename AllocA = std::allocator<A>, Container CB, Type B,
          typename AllocB = std::allocator<B>, Container CC, Type C,
          typename AllocC = std::allocator<C>, Container CD = CA,
          Type D = typename std::result_of<FN(A, B, C)>::type,
          typename AllocD = std::allocator<D>>
auto zipWith3(const FN& f, const CA<A, AllocA>& left,
              const CB<B, AllocB>& middle, const CC<C, AllocC>& right)
    -> CD<D, AllocD> {
  auto res = CD<D, AllocD>{};
  auto l = std::begin(left);
  auto m = std::begin(middle);
  auto r = std::begin(right);
  while (l != std::end(left) && m != std::end(middle) && r != std::end(right)) {
    res.emplace_back(f(*l, *m, *r));
    ++l;
    ++m;
    ++r;
  }
  return res;
}

// unzip :: [(a, b)] -> ([a], [b])
template <Container CN, typename TUP, typename AllocTUP = std::allocator<TUP>,
          Container CA = CN, Type A = typename std::tuple_element<0, TUP>::type,
          typename AllocA = std::allocator<A>, Container CB = CN,
          Type B = typename std::tuple_element<1, TUP>::type,
          typename AllocB = std::allocator<B>>
auto unzip(const CN<TUP, AllocTUP>& c)
    -> std::tuple<CA<A, AllocA>, CB<B, AllocB>> {
  auto ca = CA<A, AllocA>{};
  auto cb = CB<B, AllocB>{};
  for (const auto& t : c) {
    // wanted to use emplace_back but not
    // available for vector<bool>, maybe use back_inserter...
    ca.push_back(std::get<0>(t));
    cb.push_back(std::get<1>(t));
  }
  return std::make_tuple(ca, cb);
}

// unzip3 :: [(a, b, c)] -> ([a], [b], [c])
template <Container CN, typename TUP, typename AllocTUP = std::allocator<TUP>,
          Container CA = CN, Type A = typename std::tuple_element<0, TUP>::type,
          typename AllocA = std::allocator<A>, Container CB = CN,
          Type B = typename std::tuple_element<1, TUP>::type,
          typename AllocB = std::allocator<B>, Container CC = CN,
          Type C = typename std::tuple_element<2, TUP>::type,
          typename AllocC = std::allocator<C>>
auto unzip3(const CN<TUP, AllocTUP>& c)
    -> std::tuple<CA<A, AllocA>, CB<B, AllocB>, CC<C, AllocC>> {
  auto ca = CA<A, AllocA>{};
  auto cb = CB<B, AllocB>{};
  auto cc = CC<C, AllocC>{};
  for (const auto& t : c) {
    ca.push_back(std::get<0>(t));
    cb.push_back(std::get<1>(t));
    cc.push_back(std::get<2>(t));
  }
  return std::make_tuple(ca, cb, cc);
}
}
