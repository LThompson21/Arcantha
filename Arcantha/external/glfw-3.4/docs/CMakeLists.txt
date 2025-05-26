
# NOTE: The order of this list determines the order of items in the Guides
#       (i.e. Pages) list in the generated documentation
set(source_files
    main.md
    news.md
    quick.md
    moving.md
    compile.md
    build.md
    intro.md
    context.md
    monitor.md
    window.md
    input.md
    vulkan.md
    compat.md
    internal.md)

set(extra_files DoxygenLayout.xml header.html footer.html extra.css spaces.svg)

set(GLFW_DOXYGEN_INPUT "") # Initialize to empty string
foreach(path IN LISTS header_paths)
    string(APPEND GLFW_DOXYGEN_INPUT " \\\n\"${path}\"")
endforeach()
foreach(file IN LISTS source_files)
    string(APPEND GLFW_DOXYGEN_INPUT " \\\n\"${CMAKE_CURRENT_SOURCE_DIR}/${file}\"")
endforeach()

set(DOXYGEN_SKIP_DOT TRUE)
find_package(Doxygen)

if (NOT DOXYGEN_FOUND OR DOXYGEN_VERSION VERSION_LESS "1.9.8")
    message(STATUS "GLFW documentation generation requires Doxygen 1.9.8 or later")
else()
    # Use a unique Doxyfile name and output directory for GLFW
    configure_file(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-glfw" @ONLY) # Unique Doxyfile
    
    # Define a unique build directory for GLFW docs
    set(GLFW_DOCS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs-glfw")
    file(MAKE_DIRECTORY "${GLFW_DOCS_BUILD_DIR}") # Ensure directory exists

    add_custom_command(OUTPUT "${GLFW_DOCS_BUILD_DIR}/html/index.html" # Unique output path
                       COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-glfw" # Pass the unique Doxyfile
                       WORKING_DIRECTORY "${CMAKE_DOCS_BUILD_DIR}" # Doxygen works from its output directory
                       MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-glfw"
                       DEPENDS ${header_paths} ${source_files} ${extra_files}
                       COMMENT "Generating GLFW HTML documentation"
                       VERBATIM)

    add_custom_target(glfw_docs ALL SOURCES "${GLFW_DOCS_BUILD_DIR}/html/index.html") # Unique target name
    set_target_properties(glfw_docs PROPERTIES FOLDER "GLFW3")

    if (GLFW_INSTALL)
        install(DIRECTORY "${GLFW_DOCS_BUILD_DIR}/html" # Install from unique path
                DESTINATION "${CMAKE_INSTALL_DOCDIR}/glfw") # Unique installation subdirectory
    endif()
endif()