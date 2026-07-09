cmake_minimum_required(VERSION 3.24)
project(raylib_test)

# Force C++23 or higher
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- AUTOMATIC DEPENDENCY DOWNLOAD ---
include(FetchContent) # Enables the download manager

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com
  GIT_TAG        5.5 # Locks it to a stable version (or use 'master')
)

# Crucial settings to make Raylib build quietly inside your project
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# Download and make Raylib targets available
FetchContent_MakeAvailable(raylib)

# --- YOUR EXECUTABLE DEFINITION ---
add_executable(main main.cpp draw.cpp)

# Link the automatically downloaded raylib
target_link_libraries(main PRIVATE raylib)

# --- SYSTEM-SPECIFIC CONFIGURATIONS ---
if(APPLE)
    # macOS requires Apple framework hooks to open graphics windows
    target_link_libraries(main PRIVATE 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo"
    )
elseif(WIN32)
    # Optional Windows-only setting: Hides the black terminal console window 
    # when launching your finished Release game executable.
    set_target_properties(main PROPERTIES WIN32_EXECUTABLE TRUE)
endif()


# OLD
# cmake_minimum_required(VERSION 3.24)
# project(raylib_test)

# # Force C++23 or higher
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(raylib REQUIRED)

# # Define your executable and add source files
# add_executable(main main.cpp draw.cpp)

# # Link raylib to your game executable
# target_link_libraries(main PRIVATE raylib)
