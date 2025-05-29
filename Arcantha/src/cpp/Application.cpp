#include "Application.h" // Includes the Application class definition.
#include "InputManager.h" // Includes the InputManager class definition for input handling.
#include "Window.h" // Includes the Window class definition for window management.
#include <string> // Standard library for string operations.
#include <iostream> // Standard library for console output (e.g., std::cout).
#include <GLFW/glfw3.h> // Includes GLFW for glfwGetTime().

Application Application::instance; // Definition and initialization of the static singleton instance.

/**
 * @brief Private constructor for the Application class.
 *
 * Initializes the main window with specific properties: 800x600 resolution,
 * a purple-ish clear color (0.75, 0.5, 1, 1), title "Arcantha", not maximized on start, and resizeable.
 */
Application::Application() :
	mainWindow( 800, 600, glm::vec4( .75, .5, 1, 1 ), "Arcantha", false, true ) {}

/**
 * @brief Gets the singleton instance of the Application.
 * @return A reference to the single Application instance.
 */
Application& Application::getInstance() {
	return instance;
}

/**
 * @brief Runs the main application loop.
 *
 * This method orchestrates the application's lifecycle: initialization, main loop, and shutdown.
 */
void Application::run() {
	init(); // Initialize application components.
	loop(); // Enter the main application loop.
	shutdown(); // Shut down and clean up resources.
}

/**
 * @brief Initializes the application components.
 *
 * This includes initializing the main window and setting up the input manager
 * by passing the GLFW window pointer.
 */
void Application::init() {
	mainWindow.init(); // Initialize the main window.
	InputManager::getInstance().init( mainWindow.getGLFWwindow() ); // Initialize the input manager with the GLFW window.
}

/**
 * @brief The main application loop.
 *
 * This loop continues as long as the main window is open.
 * It handles event polling, updates the application state,
 * and calculates the delta time for frame-rate independent logic.
 */
void Application::loop() {
	double dt = -1; // Delta time, initialized to -1 to indicate the first frame.
	double frameBegin = glfwGetTime(); // Time at the beginning of the current frame.
	double frameEnd; // Time at the end of the current frame.

	while ( !mainWindow.shouldClose() ) { // Loop continues until the window is signaled to close.
		glfwPollEvents(); // Process all pending GLFW events (e.g., input, window resizing).

		update( dt ); // Update application logic with delta time.
		InputManager::getInstance().update(); // Update input states (e.g., last key states, mouse deltas).

		frameEnd = glfwGetTime(); // Get the current time for delta time calculation.
		dt = frameEnd - frameBegin; // Calculate delta time.
		frameBegin = frameEnd; // Set the current frame's end time as the next frame's start time.
	}
}

/**
 * @brief Shuts down the application.
 *
 * This method cleans up resources by shutting down the main window
 * and terminating the GLFW library.
 */
void Application::shutdown() {
	mainWindow.shutdown(); // Shut down the main window.

	glfwTerminate(); // Terminate GLFW, releasing all allocated resources.
};

/**
 * @brief Updates the application state.
 * @param dt The delta time (time elapsed since the last frame) in seconds.
 *
 * This method performs per-frame updates, including updating the main window
 * and demonstrating input manager functionality by printing key states.
 */
void Application::update( double dt ) {
	if ( dt <= 0 ) return; // Skip update if delta time is invalid (e.g., first frame).

	mainWindow.update(); // Update the main window (e.g., clear color buffer, swap buffers).

	// Debugging output for key states using InputManager.
	std::cout << "isKeyJustPressed: " << InputManager::getInstance().isKeyJustPressed( GLFW_KEY_SPACE ) << std::endl; // Checks if space was just pressed.
	std::cout << "isKeyJustReleased: " << InputManager::getInstance().isKeyJustReleased( GLFW_KEY_SPACE ) << std::endl; // Checks if space was just released.
	std::cout << "isKeyPressed: " << InputManager::getInstance().isKeyPressed( GLFW_KEY_SPACE ) << std::endl; // Checks if space is currently pressed.
}