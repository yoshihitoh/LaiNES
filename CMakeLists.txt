cmake_minimum_required(VERSION 3.1)

project(LaiNES)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE LAINES_SOURCES "src/*.cpp" "lib/*.cpp")
file(GLOB_RECURSE UNIX_SOURCES "src/porting/unix/*.cpp")
file(GLOB_RECURSE WINDOWS_SOURCES "src/porting/windows/*.cpp")

set(LAINES_HEADERS_DIRS
        "simpleini"
        "lib/include"
        "src/include"
        "third_party/sdl2/include"
        )

set(LAINES_LIBS
        SDL2
        SDL2_image
        SDL2_ttf
        )

if (WIN32)
    list(REMOVE_ITEM LAINES_SOURCES ${UNIX_SOURCES})
    set(LAINES_LIB_DIRS "")
else()
    list(REMOVE_ITEM LAINES_SOURCES ${WINDOWS_SOURCES})
    list(APPEND LAINES_HEADERS_DIRS "/usr/local/include")
    set(LAINES_LIB_DIRS "/usr/local/lib")
endif()

add_executable(LaiNES ${LAINES_SOURCES})
target_include_directories(LaiNES PRIVATE ${LAINES_HEADERS_DIRS})
target_link_directories(LaiNES PRIVATE ${LAINES_LIB_DIRS})
target_link_libraries(LaiNES ${LAINES_LIBS})