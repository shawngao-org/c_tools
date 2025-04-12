cmake_minimum_required(VERSION 3.27)
project(tools_debug C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".so") # Linux
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dylib") # macOS
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")
elseif(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dll") # Windows
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I\"C:/Program Files (x86)/tools/include\"")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L\"C:/Program Files (x86)/tools/lib\"")
endif()

add_executable(tools_debug main.c
        time_test/time_test.c
        time_test/time_test.h
        string_test/string_test.c
        string_test/string_test.h)
link_libraries(tools)
target_link_libraries(tools_debug tools)
if(CMAKE_SHARED_LIBRARY_SUFFIX STREQUAL ".dll") # Windows
    add_custom_command(
            TARGET tools_debug POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files (x86)/tools/lib/libtools.dll"
            $<TARGET_FILE_DIR:tools_debug>
            COMMENT "Copying libcurl.dll to output directory"
    )
endif()
