cmake_minimum_required(VERSION 3.27)
project(tools C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".so") # Linux
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dylib") # macOS
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dll") # Windows
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I\"C:/Program Files (x86)/cmocka/include\"")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L\"C:/Program Files (x86)/cmocka/lib\"")
endif()

file(GLOB_RECURSE SOURCES
        "src/*.c" "include/*.h"
        "src/time/*.c" "include/time/*.h"
        "src/string/*.c" "include/string/*.h"
        "src/collect/*.c" "include/collect/*.h")
add_library(tools SHARED ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(tools PRIVATE "-g")
endif()

target_include_directories(tools
        PUBLIC
        include
)

set_target_properties(tools PROPERTIES
        PUBLIC_HEADER "include/tools.h"
)

# Set install path.
install(TARGETS tools
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)

if(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".so") # Linux
    set_target_properties(tools PROPERTIES
            VERSION 1.0
            SOVERSION 1
    )
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dylib") # macOS
    set_target_properties(tools PROPERTIES
            VERSION 1.0.0
            COMPATIBILITY_VERSION 1.0
    )
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dll") # Windows
    set_target_properties(tools PROPERTIES
            VERSION 1.0.0.0
    )
endif()

# Debug and test execute
add_executable(tests
        tests/main.c
        tests/time_test/time_test.c
        tests/time_test/time_test.h
        tests/string_test/string_test.c
        tests/string_test/string_test.h
        tests/collect_test/stack_test.c
        tests/collect_test/stack_test.h
        tests/collect_test/linked_list_test.c
        tests/collect_test/linked_list_test.h)

target_link_libraries(tests PRIVATE tools)
target_link_libraries(tests PRIVATE cmocka)

option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

enable_testing()
add_test(NAME tests COMMAND tests)
