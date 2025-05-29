#include <iostream> // Required for std::cerr for error output.
#include <string> // Required for std::string operations.

#include <glad/glad.h> // Includes GLAD for OpenGL function loading.
#include <GLFW/glfw3.h> // Includes GLFW for windowing and context creation.

#include "Window.h" // Includes the Window class definition.

/**
 * @brief Constructor for the Window class.
 *
 * Initializes window properties based on provided parameters.
 * @param width The initial width of the window.
 * @param height The initial height of the window.
 * @param clear The clear color for the window.
 * @param title The title string for the window.
 * @param maximizeOnStart If true, the window will be maximized when created.
 * @param resizeable If true, the window will be resizeable by the user.
 */
Window::Window( const int width, const int height, glm::vec4 clear, const std::string& title,
	bool maximizeOnStart, bool resizeable ) :
	width( width ), height( height ), clear( clear ), title( title ), window( nullptr ), // Initialize member variables.
	maximizeOnStart( maximizeOnStart ), resizeable( resizeable ) {}

/**
 * @brief Initializes the GLFW window and OpenGL context.
 *
 * This method sets up error handling, window hints, creates the GLFW window,
 * sets up a window resize callback, makes the OpenGL context current,
 * loads OpenGL functions using GLAD, sets the swap interval,
 * makes the window visible, and enables alpha blending.
 */
void Window::init() {
	// Set GLFW error callback to print errors to stderr.
	glfwSetErrorCallback( []( int error, const char* description ) {
		std::cerr << "Err: " << error << " | " << description << std::endl;
	} );

	// Initialize GLFW. If initialization fails, print an error and exit.
	if ( !glfwInit() ) {
		std::cerr << "Err: Failure to initialize GLFW." << std::endl;
		exit( -1 ); // Exit with an error code.
	}

	glfwDefaultWindowHints(); // Set default window hints.
	glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE ); // Make window initially invisible.
	// Set window resizeability based on the 'resizeable' constructor parameter.
	glfwWindowHint( GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE );
	// Set window maximization based on the 'maximizeOnStart' constructor parameter.
	glfwWindowHint( GLFW_MAXIMIZED, maximizeOnStart ? GLFW_TRUE : GLFW_FALSE );

	// Create the GLFW window. If creation fails, print an error and exit.
	this->window = glfwCreateWindow( this->width, this->height, this->title.c_str(), NULL, NULL );
	if ( !window ) {
		std::cerr << "Err: Failure to create GLFW window." << std::endl;
		glfwTerminate(); // Terminate GLFW before exiting.
		exit( -2 ); // Exit with an error code.
	}
	glfwSetWindowUserPointer( this->window, this ); // Store a pointer to the Window instance in the GLFW window.

	// Set a window size callback to update the internal width/height and OpenGL viewport.
	glfwSetWindowSizeCallback( this->window, []( GLFWwindow* window, int w, int h ) {
		// Retrieve the Window instance from the GLFW window's user pointer.
		Window* windowInstance = static_cast< Window* >( glfwGetWindowUserPointer( window ) );
		if ( windowInstance ) {
			windowInstance->setWidth( w ); // Update the internal width.
			windowInstance->setHeight( h ); // Update the internal height.

			glViewport( 0, 0, w, h ); // Adjust the OpenGL viewport to the new window size.
		}
	} );

	glfwMakeContextCurrent( window ); // Make the window's OpenGL context current on the calling thread.
	gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ); // Load OpenGL functions using GLAD.

	glfwSwapInterval( 1 ); // Enable V-Sync (swap buffers every 1 screen refresh).

	glfwShowWindow( window ); // Make the window visible.

	glEnable( GL_BLEND ); // Enable blending for transparency.
	// Set the blending function for standard alpha blending.
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

/**
 * @brief Updates the window content.
 *
 * This method clears the color buffer with the specified clear color
 * and then swaps the front and back buffers to display the rendered frame.
 */
void Window::update() {
	// Set the clear color using the stored glm::vec4.
	glClearColor( clear.x, clear.y, clear.z, clear.w );
	glClear( GL_COLOR_BUFFER_BIT ); // Clear the color buffer bit.

	glfwSwapBuffers( window ); // Swap the front and back buffers to display the rendered frame.
}

/**
 * @brief Shuts down the window.
 *
 * This method destroys the GLFW window, releasing its resources.
 */
void Window::shutdown() {
	glfwDestroyWindow( window ); // Destroy the GLFW window.
}

/**
 * @brief Checks if the window should close.
 * @return True if the window close flag has been set, false otherwise.
 */
bool Window::shouldClose() const {
	return glfwWindowShouldClose( window );
}

/**
 * @brief Sets whether the window should close.
 * @param close True to signal the window to close, false to keep it open.
 */
void Window::setShouldClose( bool close ) {
	glfwSetWindowShouldClose( window, close );
}

/**
 * @brief Gets the underlying GLFWwindow pointer.
 * @return A pointer to the GLFWwindow object.
 */
GLFWwindow* Window::getGLFWwindow() const {
	return this->window;
}

/**
 * @brief Gets the current width of the window.
 * @return The width of the window in pixels.
 */
int Window::getWidth() const {
	return this->width;
}

/**
 * @brief Gets the current height of the window.
 * @return The height of the window in pixels.
 */
int Window::getHeight() const {
	return this->height;
}

/**
 * @brief Sets the width of the window.
 *
 * This method updates the internal `width` variable. Note that this
 * does not automatically resize the GLFW window; that is typically handled
 * by the `glfwSetWindowSizeCallback`.
 * @param width The new width for the window.
 */
void Window::setWidth( const int width ) {
	this->width = width;
}

/**
 * @brief Sets the height of the window.
 *
 * This method updates the internal `height` variable. Similar to `setWidth`,
 * this does not automatically resize the GLFW window.
 * @param height The new height for the window.
 */
void Window::setHeight( const int height ) {
	this->height = height;
}