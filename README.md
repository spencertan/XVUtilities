## XVUtilities
XVUtilities is a C++20 utility library that is a collection of containers, functionality and traits I use with my projects.

## Core 

**Types**
- Wrapper over built-in types, smart pointers, std::function
- Decay: Full decay of types
```c++
		XV::Decay<const int &> // Decayed type is int
```
- IsPointer: Concepts for pointers
- IsReference: Concepts for reference

**Typename**
- Extract a typename in compile-time

**Log**
- Logging functionality wrapping over spdlog
- Core and Application level logging

**GUID**
- A UUID/GUID phantom type

**Enumerate**
- Python style enumerate for C++

**Typelist**
- Compile-time heterogeneous container of types, similar to boost.Hana vector

**STL_C**
- Wrapper for each type of STL container
- Provide easy swapping to STL-compliant containers

**ServiceLocator**
- A service locator pattern

**EventManager**
- Event-based pattern using static polymorphism

**Hashing**
- Constexpr scalar version of XXH3
- Provide compile-time hashing for strings and Plain-Old-Data (POD) struct
- Intends to set up and toggle between the scalar version for compile-time and SIMD variant for the runtime to increase efficiency.

**Random**
- Constexpr random version of Xoshiro256SS
- With compile-time seed generator using source_location to generate new seed with XXH3

**Helper Class**
- Singleton helper class 
- UnCopyable helper class

## Traits
**ArrayType**
- Concepts::String: Check if array is string-type
- Concepts::ArrayType: Check for array type

**Function**
- Concepts::IsFunctionReturnType: Check if function's return type matches the expected type
- Type::ReturnType: Function return type
- Type::SignatureType: Signature of the function
- Type::ArgsTuple: Tuple of the arguements
- Type::args_count: count of all the arguements

**Specialised**
- IsSpecialised: Check if a type is specialised from another type

**Tuple**
- null: Nullptr of the tuple
- make_null: Nullptr of the tuple created a list of arguments
- CatType: Concatenate tuples
- Decay: Apply decay to all types in the tuple
- SortType: Sort the types in a tuple based on the comparator

## Containers
**CBitset**
- A constexpr version of std::bitset

**PinnedVector**
- A vector using VirtualAlloc, hence pointer invalidation will not happen on resizing


## External Libraries
- [tuplet](https://github.com/codeinred/tuplet) (Aggregated tuple implementation)
- [spdlog](https://github.com/gabime/spdlog) (Logging)
