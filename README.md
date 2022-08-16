# Introduction

This programming project provides an implementation and unit tests for the `sc::list<>` class.

The class describes an List Abstract Data Type, focusing in its core operations, like insertion and deletion, and how the data is stored and maintained. For this implementation, a **doubly linked list** approach is used.

A general linear list A is a set of *n* (at least zero) elements *A[0], A[1], A[2], ..., A[n - 1]*, such that for any *k > 0*, *A[k - 1]* precedes *A[k]*. 
The size of the list is naturally *n*, and if its zero, the list is said to be empty.

There are also a few operations that define the list. We can print elements in the list, clear all the contents, access specific elements based on positions, insert elements at the end of the list, or at specific positions we may want, to remove elements in the same fashion, or to remove everything within a range. Every operation is implemented in the class, and for each one there are unit tests.

Since it is a doubly linked list implementation, each node contains two pointers: one that points to the previous node in the sequence and one that points to the next node in the sequence, if there are such nodes. This provides certain advantages, such as constant O(1) insertion and deletion at any position in the list, and allows traversing in both forward and backwards directions, which also makes reversing the list quite easy. Note, however, that this means the list does not provide random access to elements.

An implementation to the list iterator is also provided, along with a constant one, which may be defined informally as a class encapsulation for a pointer to some element within the list, providing an objected oriented way of accessing the list without exposing the internal components of the class, thus preversing its encapsulation principle. For those with C++ familiarity, this implementation inherits from `std::bidirectional_iterator_tag`, which is an iterator that can be moved in both directions (decremented and incremented).

The code is well documented, so you can access the file `source/include/list.h` to read the functions and some Doxygen style documentation explaining them. The tests are divided in: 24 unit tests for the list class and 9 unit tests for the iterator class, along with 22 tests for the utility operations, such as sorting (which is using a merge sort implementation for stability, check it out).

# Organization

The folders and files of this project are the following:

* `source/tests/include`: This contains the library that provides supports for the unit tests.
* `source/tests`: This folder has the file `main.cpp` that contains all the tests.
* `source/include`: This folder has the file `list.h` which is the implementation of the list.
* `source/CMakeLists.txt`: The cmake script file.
* `README.md`: This file.

# Compiling

This project may be compiled with [CMake](https://cmake.org). CMake is an open-source, cross-platform family of tools designed to build, test and package software. Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.
Alternatively, the same script might be used to create Xcode projects, Ninja, or Microsoft Visual Studio projects, for instance.

CMake supports **out-of-source** build. This means the _source code_ is stored in **one** folder and the _generated executable files_ should be stored in **another** folder: project should never mix-up the source tree with the build tree.

In particular, this project creates a single **target** (executable), called `run_tests`.

But don't worry, they are already set up in the `CMakeLists.txt` script.

To compile this project with [cmake](https://cmake.org) follow these steps (from the root folder):

1. `cmake -S source -B build`:  asks cmake to create the build directory and generate the Unix Makefile based on the script found in `source/CMakeLists.txt`, on the current level.
3. `cmake --build build`: triggers the compiling process that creates both targets (executable).D inside `build`.

The executable is created inside the `build` directory.

For further details, please refer to the [cmake documentation website](https://cmake.org/cmake/help/v3.14/manual/cmake.1.html).

We have in this project two batches of tests: 24 unit tests for the `sc::list` class, and 9 unit tests for the `sc::list::iterator` class, and 22 tests for the utility operations.

## Compiling without CMake

If you wish to compile this project without the cmake, create the `build` folder manually (`mkdir build`), and a `tests` folder inside it, then try to run the command below from the root folder:

```
g++ -Wall -std=c++11 -I source/include -I source/tests/include/tm source/tests/main.cpp source/tests/include/tm/test_manager.cpp -o build/tests/run_tests
```

# Running

From the project's root folder, run as usual (assuming `$` is the terminal prompt):

```
$ ./build/tests/all_tests
```
