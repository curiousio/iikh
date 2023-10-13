# Interactive Intelligent Kitchen Helper

## Introduction

Interactive Intelligent Kitchen Helper (IIKH) is a simple CLI based meal planner written in C++ utilizing SQLite.

## Features

* Recipe management
* Plan management based on Recipe

## Requirements

* Microsoft Windows 11 (recommended)
* C++14
* SQLite3

## Installation

Clone this repository.

```shell
git clone https://github.com/curiousio/iikh.git
```

Checkout to the desired version.

```shell
git checkout vMAJOR.MINOR.PATCH
```

### GNU/Linux

Install the SQLite3 library via the system package manager.

#### Debian-based

```shell
sudo apt install libsqlite3-dev
```

#### RPM-based

```shell
sudo dnf install sqlite-devel
```

## Execution

### Linux/G++

Build from the source and run the application.

```shell
g++ main.cpp -std=c++14 -l sqlite3
./a.out
```

* Warning: Because Linux's system call is different from Windows, you can see the error or warning when executing the program.
* Please modify `system()` before executing program.

### Windows/MSVC

You have two options.

#### Execute the program only

Go to [Releases](https://github.com/curiousio/iikh/releases) and download `IIKH.exe`.

#### Build yourself

1. Open `IIKH.sln` with Visual Studio 2022
2. Build

## License

IIKH is released under the AGPL-3.0 license.
