cmake_minimum_required(VERSION 3.24)
project(raylib_test)

# Force C++23 or higher
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

# Define your executable and add source files
add_executable(main main.cpp draw.cpp)

# Link raylib to your game executable
target_link_libraries(main PRIVATE raylib)
