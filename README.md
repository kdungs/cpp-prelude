# cpp-prelude
[![Build Status](https://travis-ci.org/kdungs/cpp-prelude.svg?branch=master)](https://travis-ci.org/kdungs/cpp-prelude)

Implement functionality from Haskell's Prelude in C++11. Just for fun. Errors guaranteed.

After playing around with [functional immutable lists in C++11](https://github.com/kdungs/cpp-list), I though it would be nice to have the functionality from Haskell's Prelude (or at least the interesting functions) in C++. This is an attempt to implement some of the functionality on STL containers. Whenever possible, functionality from the STL is used.

## Functionality

### List operations

 * [x] `map :: (a -> b) -> [a] -> [b]`
 * [x] `(++) :: [a] -> [a] -> [a]` as `join`
 * [x] `filter :: (a -> Bool) -> [a] -> [a]`
 * [x] `head :: [a] -> a`
 * [x] `last :: [a] -> a`
 * [x] `tail :: [a] -> [a]`
 * [x] `init :: [a] -> [a]`
 * [x] `null :: [a] -> Bool`
 * [x] `length :: [a] -> Int`
 * [x] `(!!) :: [a] -> Int -> a` as `at`
 * [x] `reverse :: [a] -> [a]`

### Reducing lists (folds)

 * [x] `foldl :: (b -> a -> b) -> b -> [a] -> b`
 * [x] `foldl1 :: (a -> a -> a) -> [a] -> a`
 * [x] `foldr :: (a -> b -> b) -> b -> [a] -> b`
 * [x] `foldr1 :: (a -> a -> a) -> [a] -> a`

### Special folds

 * [ ] `and :: [Bool] -> Bool`
 * [ ] `or :: [Bool] -> Bool`
 * [ ] `any :: (a -> Bool) -> [a] -> Bool`
 * [ ] `all :: (a -> Bool) -> [a] -> Bool`
 * [ ] `sum :: Num a => [a] -> a`
 * [ ] `product :: Num a => [a] -> a`
 * [ ] `concat :: [[a]] -> [a]`
 * [ ] `concatMap :: (a -> [b]) -> [a] -> [b]`
 * [ ] `maximum :: Ord a => [a] -> a`
 * [ ] `minimum :: Ord a => [a] -> a`

### Building lists

 * [ ] `scanl :: (b -> a -> b) -> b -> [a] -> [b]`
 * [ ] `scanl1 :: (a -> a -> a) -> [a] -> [a]`
 * [ ] `scanr :: (a -> b -> b) -> b -> [a] -> [b]`
 * [ ] `scanr1 :: (a -> a -> a) -> [a] -> [a]`


### Infinite lists

Without lazy evaluation, there is not really any way to produce infinite
lists. Maybe I'll implement these functions with an additional size
parameter.

### Sublists

 * [ ] `take :: Int -> [a] -> [a]`
 * [ ] `drop :: Int -> [a] -> [a]`
 * [ ] `splitAt :: Int -> [a] -> ([a], [a])`
 * [ ] `takeWhile :: (a -> Bool) -> [a] -> [a]`
 * [ ] `dropWhile :: (a -> Bool) -> [a] -> [a]`
 * [ ] `span :: (a -> Bool) -> [a] -> ([a], [a])`
 * [ ] `break :: (a -> Bool) -> [a] -> ([a], [a])`

### Searching lists

 * [ ] `elem :: Eq a => a -> [a] -> Bool`
 * [ ] `notElem :: Eq a => a -> [a] -> Bool`
 * [ ] `lookup :: Eq a => a -> [(a, b)] -> Maybe b`

### Zipping and unzipping lists 

 * [ ] `zip :: [a] -> [b] -> [(a, b)]`
 * [ ] `zip3 :: [a] -> [b] -> [c] -> [(a, b, c)]`
 * [ ] `zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]`
 * [ ] `zipWith3 :: (a -> b -> c -> d) -> [a] -> [b] -> [c] -> [d]`
 * [ ] `unzip :: [(a, b)] -> ([a], [b])`
 * [ ] `unzip3 :: [(a, b, c)] -> ([a], [b], [c])`
