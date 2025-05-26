# Arcantha/tests/CMakeLists.txt

# Do NOT include the parent CMakeLists.txt.
# We are already in a subdirectory added by the parent, so its targets are available.

project(Arcantha_Tests LANGUAGES CXX C)

# --- Test Executables ---

# All targets defined in the parent's CMakeLists.txt (glfw, glad, OpenAL, Box2D, ImGui)
# are already available in this subdirectory's scope because 'tests' was added via add_subdirectory().
# Their PUBLIC include directories and linked libraries are inherited.

# Test GLFW
add_executable(test_glfw test_glfw.cpp)
target_link_libraries(test_glfw PRIVATE glfw) # 'glfw' target is available from parent

# Test GLAD
add_executable(test_glad test_glad.cpp)
target_link_libraries(test_glad PRIVATE glad glfw) # 'glad' target is available from parent

# Test OpenAL Soft
add_executable(test_openal test_openal.cpp)
target_link_libraries(test_openal PRIVATE OpenAL) # 'OpenAL' target is available from parent

# Test Box2D
add_executable(test_box2d test_box2d.cpp)
target_link_libraries(test_box2d PRIVATE box2d glfw ImGui) # 'Box2D' target is available from parent

# Test stb_image
add_executable(test_stb_image test_stb_image.cpp)
target_compile_definitions(test_stb_image PRIVATE STB_IMAGE_IMPLEMENTATION)
# The parent 'Arcantha' target sets up STB_DIR and include paths.
# If test_stb_image needs these includes, you can either:
# 1. Link against the 'Arcantha' target (if 'Arcantha' exposes includes publicly, not recommended for tests)
# 2. Explicitly add the include directory here (preferred for tests if not exposed PUBLICly by library targets)
# Let's assume the parent's 'target_include_directories' for Arcantha handles this broadly.
# If not, you might need to add:
target_include_directories(test_stb_image PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../external/stb")


# Test GLM (Header-only, no explicit linking needed, just include path)
# add_executable(test_glm test_glm.cpp)
# Similar to stb_image, GLM's include path should be handled.
# target_include_directories(test_glm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../external/glm-1.0.1")


# Test ImGui
# add_executable(test_imgui test_imgui.cpp)
# target_link_libraries(test_imgui PRIVATE ImGui glfw glad) # ImGui often needs GLFW/OpenGL backends, so link them.

# --- Platform-specific linking ---
# These are still necessary for the test executables as they are new executables.
if(WIN32)
    target_link_libraries(test_glfw PRIVATE gdi32 opengl32)
    target_link_libraries(test_glad PRIVATE opengl32)
    # target_link_libraries(test_imgui PRIVATE gdi32 opengl32)
endif()

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(test_glfw PRIVATE X11::X11 Xrandr Xi GL)
    target_link_libraries(test_glad PRIVATE GL)
    # target_link_libraries(test_imgui PRIVATE X11::X11 Xrandr Xi GL)
endif()

# Optional: Set C++ standard for tests
set_property(TARGET test_glfw test_glad test_openal test_box2d test_stb_image PROPERTY CXX_STANDARD 17) # test_glm test_imgui
set_property(TARGET test_glfw test_glad test_openal test_box2d test_stb_image PROPERTY CXX_STANDARD_REQUIRED ON) # test_glm test_imgui
set_property(TARGET test_glfw test_glad test_openal test_box2d test_stb_image PROPERTY CXX_EXTENSIONS OFF) # test_glm test_imgui