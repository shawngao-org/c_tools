# C Tools

[![Build](https://github.com/shawngao-org/c_tools/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/shawngao-org/c_tools/actions/workflows/build.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=shawngao-org_c_tools&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=shawngao-org_c_tools)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=shawngao-org_c_tools&metric=bugs)](https://sonarcloud.io/summary/new_code?id=shawngao-org_c_tools)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=shawngao-org_c_tools&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=shawngao-org_c_tools)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=shawngao-org_c_tools&metric=coverage)](https://sonarcloud.io/summary/new_code?id=shawngao-org_c_tools)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=shawngao-org_c_tools&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=shawngao-org_c_tools)

+ This project is a C language tool library.
+ This project will encapsulate some commonly used tools and functions.
+ This project has not been developed yet and many functions need to be added.

## Build & Run

#### Requirements

+ CMake 3.27 or higher

#### Linux & macOS

```shell
# build and test
./build.sh
./build/tests
```

#### Windows

> You need to install `Cygwin`(Recommended) or `MingW` to compile and run Windows programs.

> If you want to use `MingW` to compile and run Windows programs, you need to change `build.bat` file.

```shell
# build and test
.\build.bat
.\build\tests.exe
```

## Usage

### Install library to system, or include library in your project

#### Install library to system

> This method is not supported for Windows. Please see [Include library in your project](#include-library-in-your-project).

```shell
cd build
make install
# If Linux OS
sudo ldconfig
```

#### Include library in your project

Create `lib` directory in your project and create `include` directory in `lib` directory.

```text
project_root/
├── CMakeLists.txt
└── lib/
    └── include/
```

Copy `include/tools.h` to `lib/include/` directory.

Copy libraries to `lib` directory:

+ MacOS: `build/libtools.dylib` and `build/libtools.1.0.0.dylib`

+ Linux: `build/libtools.so` and `build/libtools.so.1.0`

+ Windows + Cygwin: `build/libtools.dll.a` and `build/cygtools.dll`

+ Windows + MingW: `build/libtools.dll.a` and `build/libtools.dll`

```text
project_root/
├── CMakeLists.txt
└── lib/
    ├── include/
    │   └── tools.h
    ├── libtools.dll # Windows with MingW
    ├── cygtools.dll # Windows with Cygwin
    ├── libtools.dll.a # Windows
    ├── libtools.so # Linux
    ├── libtools.so.1.0 # Linux
    ├── libtools.dylib # macOS
    └── libtools.1.0.0.dylib # macOS
```

CMakeLists.txt example:

```cmake
# tools_example replace with your project name
cmake_minimum_required(VERSION 3.27)
project(tools_example C)

set(CMAKE_C_STANDARD 11)

add_executable(tools_example main.c)

target_include_directories(tools_example PRIVATE lib/include)
target_link_directories(tools_example PRIVATE lib)
target_link_libraries(tools_example tools)
```

main.c example:

```c
#include "tools.h"

int main() {
    hello();
    return 0;
}
```

If you run `./tools_example` you will see:

```text
Hello, World!
```

This means you can use this library for development.

## Bugs

+ If you find a bug, please open an issue.
+ If you want to fix a bug or add a feature, please open a pull request.

## Contributing

+ Fork this repository.
+ Make your changes.
+ Commit your changes.
+ Push your changes.
+ Create a pull request.
+ Wait for the maintainer to review your pull request.

## License
This project is licensed under the **MIT** License - see the LICENSE.md file for details.

## Acknowledgments

### CLion

> CLion is an IDE that maximizes developer productivity in every aspect.

Special thanks to JetBrains for providing a free CLion license for open source and educational learning.

<img src="./image/jetbrains-variant-3.png" alt="Logo" width="200"/>

### SonarQube Cloud

> SaaS solution for high quality code. Simple, scalable, fast.

Special thanks to SonarSource for providing a free SonarQube Cloud Free Plan for open source.

<img src="https://assets-eu-01.kc-usercontent.com/5dddefee-e8bb-013a-3b4e-7907971cf825/049542ea-4991-4e9e-81ea-8744c3ae685b/SQ-Cloud_Horizontal%402x.png" alt="Logo" width="200"/>

### Sourcery AI

> Sourcery is an AI-powered code review tool that helps developers find bugs, vulnerabilities, and security issues in their code.

Special thanks to Sourcery for providing a free plan Sourcery AI for open source.

<img src="https://sourcery.ai/_astro/sourcery-dark.CjCiMq8g_Z1W5FsC.svg" alt="Logo" width="200">
