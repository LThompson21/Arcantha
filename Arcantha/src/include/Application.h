#pragma once 

#include <string> // Required for std::string operations.

#include "Window.h" // Includes the Window class definition, which Application depends on.

/**
 * @brief The Application class represents the main application instance.
 *
 * This class implements the Singleton design pattern to ensure only one instance
 * of the application exists throughout the program's lifecycle. It manages the
 * main window, initializes the input system, and runs the main application loop.
 */
class Application
{
public:
	/**
	 * @brief Gets the singleton instance of the Application.
	 * @return A reference to the single Application instance.
	 */
	static Application& getInstance();
	/**
	 * @brief Runs the main application loop.
	 *
	 * This method initializes the application, enters the main loop, and then
	 * shuts down the application gracefully.
	 */
	void run();

private:
	static Application instance; // The single instance of the Application class, implementing the Singleton pattern.

	Window mainWindow; // The main window of the application.

	/**
	 * @brief Private constructor to enforce Singleton pattern.
	 *
	 * Initializes the mainWindow with default dimensions (800x600), clear color (purple-ish), title "Arcantha",
	 * and window properties (not maximized on start, resizeable).
	 */
	Application();
	/**
	 * @brief Default destructor.
	 */
	~Application() = default;

	/**
	 * @brief Initializes the application.
	 *
	 * This includes initializing the main window and the input manager.
	 */
	void init();
	/**
	 * @brief The main application loop.
	 *
	 * This loop continues as long as the main window should not close.
	 * It polls GLFW events, updates the application state, and calculates
	 * the delta time between frames.
	 */
	void loop();
	/**
	 * @brief Shuts down the application.
	 *
	 * This method cleans up resources, including destroying the main window
	 * and terminating GLFW.
	 */
	void shutdown();

	/**
	 * @brief Updates the application state.
	 * @param dt The delta time (time elapsed since the last frame) in seconds.
	 */
	void update( double dt );
};