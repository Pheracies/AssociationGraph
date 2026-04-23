# AssociationGraph

A small C++20 template library for building and exploring graphs of arbitrary value types.
Each vertex stores a value and its adjacency list; graphs can contain other graphs as
values, with automatic back-pointers to the contained graph detected at compile time.

## Features
- `Vertex<T>` and `Graph<T>` templates — works with any value type.
- Adjacency-list representation (neighbors stored per-vertex).
- Nested graphs: `Graph<Graph<T>>` auto-tracks the contained graph via a custom
  `IsGraph<T>` trait and `if constexpr`.
- Recursive builder for generating multi-level graph hierarchies.

## Build
CMake + Ninja, MSVC or Clang with C++20.

    cmake --preset x64-debug
    cmake --build out/build/x64-debug

## Status
Learning project — APIs unstable, no edge-removal or weighted edges yet.
