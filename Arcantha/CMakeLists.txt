# Arcantha/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Arcantha LANGUAGES CXX C)

# Set warning level
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Arcantha/
# ├── CMakeLists.txt
# ├── external/
# │   ├── box2d-2.4.2/
# │   ├── glad/
# │   ├── glfw-3.4/
# │   ├── glm-1.0.1/
# │   ├── imgui-1.91.9b/
# │   ├── openal-soft-1.24.0/
# │   └── stb/
# ├── src/
# │   ├── cpp/
# │   ├── include/
# │   └── main.cpp
# ├── tests/
# │   ├── CMakeLists.txt
# │   ├── test_XXXX.cpp   
# │   └── ...

# Define the source and include directories for your project
set(Arcantha_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/cpp")
set(Arcantha_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/include")

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
set(OPENAL_SOFT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/openal-soft-1.24.0") # Adjust version
# OpenAL Soft has its own CMake options; you might want to disable some
# features you don't need to reduce build time/binary size.
# For example, to build as a static library (common for games):
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Ensures static build for OpenAL Soft
set(ALSOFT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable examples
set(ALSOFT_BUILD_TESTS OFF CACHE BOOL "" FORCE)   # Disable tests
set(ALSOFT_EMBED_CORE_DATA ON CACHE BOOL "" FORCE) # Embed default configuration
add_subdirectory(${OPENAL_SOFT_SOURCE_DIR})

# --- Box2D Setup ---
set(BOX2D_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/box2d-2.4.2")
# Prevent Box2D from building its examples or tests, which often depend on
# rendering libraries like GLFW, GLAD, and ImGui, avoiding potential conflicts
# with your main project's direct linking to these libraries.
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Disable Box2D unit tests" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Disable Box2D testbed" FORCE)
add_subdirectory(${BOX2D_SOURCE_DIR})

# --- stb_image Setup ---
set(STB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/stb")
# No add_library or add_subdirectory for stb_image as it's a single header with implementation in one .cpp

# --- GLM Setup ---
set(GLM_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glm-1.0.1")
# No add_library or add_subdirectory for GLM as it's header-only

# --- Dear ImGui Setup ---
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.91.9b")
# List all ImGui source files you've placed in your external/imgui directory
set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

# Create a static library for ImGui
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${GLFW_SOURCE_DIR}/include"
    "${GLAD_SOURCE_DIR}/include"
)

# --- Executable Setup ---
add_executable(Arcantha "src/main.cpp"
    "src/include/Application.h" "src/cpp/Application.cpp"
    "src/include/Window.h" "src/cpp/Window.cpp"
    "src/include/Input.h" "src/cpp/Input.cpp")

# Link GLFW, GLAD, OpenAL, Box2D, and ImGui to your executable
target_link_libraries(Arcantha PUBLIC glfw glad OpenAL box2d ImGui)

# Tell the compiler to look for headers in your project's include directory
target_include_directories(Arcantha PUBLIC
    ${Arcantha_INCLUDE_DIR}           # Your project's headers
    ${GLFW_SOURCE_DIR}/include        # GLFW headers
    ${GLAD_SOURCE_DIR}/include        # GLAD headers
    ${OPENAL_SOFT_SOURCE_DIR}/include # OpenAL Soft headers
    ${STB_DIR}                        # stb_image header
    ${GLM_SOURCE_DIR}                 # GLM headers
    ${BOX2D_SOURCE_DIR}/include       # box2d headers
)

# Ensure stb_image is defined
target_compile_definitions(Arcantha PUBLIC STB_IMAGE_IMPLEMENTATION GLFW_INCLUDE_NONE)

# Optional: Set C++ standard (e.g., C++17)
set_property(TARGET Arcantha PROPERTY CXX_STANDARD 17)
set_property(TARGET Arcantha PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET Arcantha PROPERTY CXX_EXTENSIONS OFF)

# --- Platform-specific considerations for OpenGL linking ---
if(WIN32)
    target_link_libraries(Arcantha PUBLIC gdi32 opengl32)
endif()

if(UNIX AND NOT APPLE) # Linux specific
    find_package(X11 REQUIRED)
    target_link_libraries(Arcantha PUBLIC X11::X11 Xrandr Xi GL)
endif()

# Note: OpenAL Soft's CMake will handle its own platform-specific linking (e.g., WinMM on Windows, ALSA/PulseAudio on Linux).

# --- Add the tests subdirectory ---
add_subdirectory(tests)
