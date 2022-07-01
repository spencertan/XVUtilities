## XVUtilities
This is a C++20 utility library that is a collection of containers, functionality and traits that I am using with my projects.

## List of all functionality

**Core**
- Types: Wrapper and aliases over base type
- GUID: Phantom typing for UUID/GUID
- Log: Logging functionality wrapped over spdlog
- Typename: Extract typename in compile-time
- Typelist: A compile-time heterogeneous container for modifying types
- STL Container Wrapper: A wrapper over all STL
- Event Manager: A event-based pattern
- Service Locator: A service locator pattern
- Singleton base class
- NonCopyable base class
- XXH3: A compile-time version based on the XXH3 hashing algorithm

**Traits**
- Array: Support std::array, std::vector, std::span and C-style array 
- Function: Generate information for lambda, method, functor, function
- Tuple: Compile-time tuplet sorting tuplet::tuple (Can be modified to support std::tuple)
- Specialised: Check specialisation for template type

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
- SortType: Sort the types in a tuple based on comparator

**Containers**
- CBitset: Compile time bitset
- PinnedVector: A vector using VirtualAlloc, hence pointer invalidation will not happened on resizing


## External Libraries
- [tuplet](https://github.com/codeinred/tuplet) (Aggregated tuple implementation)
- [spdlog](https://github.com/gabime/spdlog) (Logging)
