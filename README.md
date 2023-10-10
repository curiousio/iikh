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

### Linux/G++

Build from the source and run the application.

```shell
g++ main.cpp -l sqlite3
./a.out
```

* Warning: Because Linux's system call is different from Windows, you can see the error or warning when executing the program.
* Please modify `system()` before executing program.

### Windows/MSVC

1. Make New C++ Empty Project
2. Copy the `sqlite` directory into `Header Files` and the source code into `Source Files`
3. Bulid

## License

IIKH is released under the AGPL-3.0 license.
