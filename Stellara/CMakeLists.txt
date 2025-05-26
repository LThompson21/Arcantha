# my_project/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Workspace LANGUAGES CXX)

# Assuming you put headers in 'include' directory:
# my_project/
# ├── CMakeLists.txt
# ├── src/
# │   ├── cpp/
# │   │   └── source.cpp
# │   ├── include/
# │   │   └── source.h
# │   └── main.cpp

add_executable(App src/main.cpp 
    # Other src files
    src/cpp/source.cpp
)

# Tell the compiler to look for headers in the 'include' directory
target_include_directories(App PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)