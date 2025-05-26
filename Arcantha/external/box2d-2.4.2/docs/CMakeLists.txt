
# NOTE: The order of this list determines the order of items in the Guides
#       (i.e. Pages) list in the generated documentation

set(BOX2D_DOXYGEN_SOURCES
    "include/box2d"
    "docs/overview.md"
    "docs/hello.md"
    "docs/testbed.md"
    "docs/common.md"
    "docs/collision.md"
    "docs/dynamics.md"
    "docs/loose_ends.md"
    "docs/references.md"
    "docs/FAQ.md")

set(BOX2D_DOXYGEN_INPUT "") # Initialize to empty string
foreach(path IN LISTS BOX2D_DOXYGEN_SOURCES)
    string(APPEND BOX2D_DOXYGEN_INPUT " \\\n\"${CMAKE_SOURCE_DIR}/${path}\"")
endforeach()

# Use a unique Doxyfile name and output directory for Box2D
configure_file(Doxyfile.in "${CMAKE_BINARY_DIR}/Doxyfile-box2d" @ONLY) # Unique Doxyfile

# Define a unique build directory for Box2D docs
set(BOX2D_DOCS_BUILD_DIR "${CMAKE_BINARY_DIR}/docs-box2d")
file(MAKE_DIRECTORY "${BOX2D_DOCS_BUILD_DIR}") # Ensure directory exists

add_custom_target(box2d_docs ALL "${DOXYGEN_EXECUTABLE}" "${CMAKE_BINARY_DIR}/Doxyfile-box2d" # Pass the unique Doxyfile
                  WORKING_DIRECTORY "${BOX2D_DOCS_BUILD_DIR}" # Doxygen works from its output directory
                  COMMENT "Generating Box2D HTML documentation" VERBATIM) # Unique target name

install(
    DIRECTORY "${BOX2D_DOCS_BUILD_DIR}/html" # Install from unique path
    DESTINATION "${CMAKE_INSTALL_DOCDIR}/box2d" # Unique installation subdirectory
)