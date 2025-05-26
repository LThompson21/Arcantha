cmake_minimum_required(VERSION 3.10)
project(Stellara LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17) # Or a newer standard if desired
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define source directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${SRC_DIR}/include")

# Add your main executable
add_executable(Stellara
    ${SRC_DIR}/main.cpp
    # Add other .cpp files here as they are created, e.g.,
    # ${SRC_DIR}/cpp/source.cpp
)

# Tell the compiler to look for headers in the 'include' directory
target_include_directories(Stellara PRIVATE
    ${INCLUDE_DIR}
)

# Add external directory where libraries will reside
add_subdirectory(external)

# In your main CMakeLists.txt or a dedicated file for external libs
target_include_directories(Stellara PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm # Path to where glm is extracted
)