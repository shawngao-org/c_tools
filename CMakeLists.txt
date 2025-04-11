cmake_minimum_required(VERSION 3.27)
project(tools C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.c" "include/*.h" "src/time/*.c" "include/time/*.h")
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
