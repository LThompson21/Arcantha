#pragma once

#include <string> // Required for std::string to store the window title.

#include <glm/glm.hpp> // Includes GLM for glm::vec4, used for the clear color.
#include <GLFW/glfw3.h> // Includes GLFW library for window creation and management.

/**
 * @brief The Window class manages a GLFW window.
 *
 * This class handles the creation, updating, and shutting down of a graphical window
 * using GLFW. It also manages window properties such as dimensions, title,
 * clear color, and resizeability.
 */
class Window
{
public:
	/**
	 * @brief Constructor for the Window class.
	 * @param width The initial width of the window in pixels.
	 * @param height The initial height of the window in pixels.
	 * @param clear The clear color for the window (R, G, B, A).
	 * @param title The title string for the window.
	 * @param maximizeOnStart If true, the window will be maximized when created.
	 * @param resizeable If true, the window will be resizeable by the user.
	 */
	Window( const int width, const int height, glm::vec4 clear, const std::string& title, bool maximizeOnStart, bool resizeable );
	/**
	 * @brief Default destructor for the Window class.
	 */
	~Window() = default;

	/**
	 * @brief Initializes the GLFW window and OpenGL context.
	 *
	 * Sets up error callbacks, GLFW window hints, creates the window,
	 * sets user pointer, registers size callback, makes context current,
	 * loads GLAD, sets swap interval, shows the window, and enables blending.
	 */
	void init();
	/**
	 * @brief Updates the window content.
	 *
	 * Clears the color buffer with the specified clear color and swaps the front and back buffers.
	 */
	void update();
	/**
	 * @brief Shuts down the window, destroying the GLFW window.
	 */
	void shutdown();

	/**
	 * @brief Checks if the window should close.
	 * @return True if the window should close, false otherwise.
	 */
	bool shouldClose() const;
	/**
	 * @brief Sets whether the window should close.
	 * @param shouldClose True to signal the window to close, false otherwise.
	 */
	void setShouldClose( bool shouldClose );

	/**
	 * @brief Gets the underlying GLFWwindow pointer.
	 * @return A pointer to the GLFWwindow object.
	 */
	GLFWwindow* getGLFWwindow() const;
	/**
	 * @brief Gets the current width of the window.
	 * @return The width of the window in pixels.
	 */
	int getWidth() const;
	/**
	 * @brief Gets the current height of the window.
	 * @return The height of the window in pixels.
	 */
	int getHeight() const;

	/**
	 * @brief Sets the width of the window.
	 * @param width The new width for the window.
	 */
	void setWidth( const int width );
	/**
	 * @brief Sets the height of the window.
	 * @param height The new height for the window.
	 */
	void setHeight( const int height );

private:
	GLFWwindow* window; // Pointer to the GLFW window object.
	int width, height; // Current dimensions of the window.
	glm::vec4 clear; // The clear color for the window.
	const std::string title; // The title of the window.
	bool maximizeOnStart, resizeable; // Window properties.
};