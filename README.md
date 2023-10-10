# Interactive Intelligent Kitchen Helper

## Introduction

Interactive Intelligent Kitchen Helper (IIKH) is a simple CLI based meal planner written in C++ utilizing SQLite.

## Features

* Recipe management
* Plan management based on Recipe

## Requirements

* Microsoft Windows 11
* C++14
* SQLite3

## Installation

Clone this repository.

```shell
git clone https://github.com/curiousio/iikh.git
```

Checkout to the desired version.

```shell
git checkout v1.0.0
```

## Execution

* ### Linux/GCC

Build from the source and run the application.

```shell
g++ main.cpp -l sqlite3
./a.out
```
* Warning : Becuase Linux's System Call is different from Windows, You can see the Error or Warning when you execute the program.
* Please Modify system() before executing program. 

*****

* ### Windows/MSVC

1. Make New C++ Empty Project
2. Copy the `sqlite` directory into `Header Files` and the source code into `Source Files`
3. Bulid

## License

IIKH is released under the AGPL-3.0 license.
