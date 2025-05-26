# Stellara/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Stellara LANGUAGES CXX)

# Define the source and include directories for your project
set(STELLARA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")
set(STELLARA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")

# --- GLFW Setup ---
set(GLFW_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.4")
add_subdirectory(${GLFW_SOURCE_DIR})

# --- GLAD Setup ---
set(GLAD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glad")
add_library(glad STATIC
    "${GLAD_SOURCE_DIR}/src/glad.c"
)
target_include_directories(glad PUBLIC
    "${GLAD_SOURCE_DIR}/include"
)

# --- OpenAL Soft Setup ---
set(OPENAL_SOFT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/openal-soft-1.23.1") # Adjust version
# OpenAL Soft has its own CMake options; you might want to disable some
# features you don't need to reduce build time/binary size.
# For example, to build as a static library (common for games):
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Ensures static build for OpenAL Soft
set(ALSOFT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable examples
set(ALSOFT_BUILD_TESTS OFF CACHE BOOL "" FORCE)   # Disable tests
set(ALSOFT_EMBED_CORE_DATA ON CACHE BOOL "" FORCE) # Embed default configuration
add_subdirectory(${OPENAL_SOFT_SOURCE_DIR})


# --- Executable Setup ---
add_executable(Stellara
    src/main.cpp
    ${STELLARA_SRC_DIR}/source.cpp # Example: Add other source files here
)

# Link GLFW, GLAD, and OpenAL to your executable
target_link_libraries(Stellara PRIVATE glfw glad OpenAL) # The target name from OpenAL Soft's CMake is typically 'OpenAL'

# Tell the compiler to look for headers in your project's include directory
target_include_directories(Stellara PRIVATE
    ${STELLARA_INCLUDE_DIR}
    ${GLFW_SOURCE_DIR}/include # GLFW headers
    ${GLAD_SOURCE_DIR}/include # GLAD headers
    ${OPENAL_SOFT_SOURCE_DIR}/include # OpenAL headers (usually just 'AL/al.h', 'AL/alc.h')
)

# Optional: Set C++ standard (e.g., C++17)
set_property(TARGET Stellara PROPERTY CXX_STANDARD 17)
set_property(TARGET Stellara PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET Stellara PROPERTY CXX_EXTENSIONS OFF)

# --- Platform-specific considerations for OpenGL linking ---
if(WIN32)
    target_link_libraries(Stellara PRIVATE gdi32 opengl32)
endif()

if(UNIX AND NOT APPLE) # Linux specific
    find_package(X11 REQUIRED)
    target_link_libraries(Stellara PRIVATE X11::X11 Xrandr Xi GL)
endif()

# Note: OpenAL Soft's CMake will handle its own platform-specific linking (e.g., WinMM on Windows, ALSA/PulseAudio on Linux).