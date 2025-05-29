#pragma once
#include <vector> // Required for std::vector to hold listeners.
#include <functional> // Required for std::function to store callable objects (listeners).
#include <GLFW/glfw3.h> // Includes GLFW library for input handling functions and constants.
#include <glm/glm.hpp> // Includes GLM for vector types like glm::vec2, used for positions and deltas.
#include <map> // Required for std::map to store key and mouse button states.

/**
 * @brief Base structure for all input events.
 *
 * Provides flags to control event consumption by listeners.
 */
struct BaseEvent
{
	bool consumable = true; // Indicates if the event can be consumed by a listener, stopping further propagation.
	bool consumed = false; // Indicates if the event has already been consumed by a listener.
};

/**
 * @brief Structure for keyboard key events.
 */
struct KeyEvent : BaseEvent
{
	int key; // The keyboard key that was pressed or released (e.g., GLFW_KEY_SPACE).
	int scancode; // The system-specific scancode of the key.
	int action; // The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
	int mods; // Modifier flags (e.g., GLFW_MOD_SHIFT, GLFW_MOD_CONTROL).
};

/**
 * @brief Structure for mouse button events.
 */
struct MouseButtonEvent : BaseEvent
{
	int button; // The mouse button that was pressed or released (e.g., GLFW_MOUSE_BUTTON_LEFT).
	int action; // The action (GLFW_PRESS, GLFW_RELEASE).
	int mods; // Modifier flags (e.g., GLFW_MOD_SHIFT).
	double xPos, yPos; // Mouse cursor position when the event occurred.
};

/**
 * @brief Structure for mouse movement events.
 */
struct MouseMoveEvent : BaseEvent
{
	double xPos, yPos; // Current mouse cursor position.
	double xDelta, yDelta; // Change in mouse cursor position since the last update.
};

/**
 * @brief Structure for mouse scroll events.
 */
struct MouseScrollEvent : BaseEvent
{
	double xOffset, yOffset; // The scroll offset along the X and Y axes.
};

/**
 * @brief Manages event listeners and dispatches events.
 *
 * This class provides vectors of std::function objects to hold listeners
 * for different types of input events. It allows dispatching events to all
 * registered listeners.
 */
class EventDispatcher
{
public:
	// Vectors to hold listener functions for different event types.
	std::vector<std::function<void( const KeyEvent& )>> keyListeners;
	std::vector<std::function<void( const MouseButtonEvent& )>> mouseButtonListeners;
	std::vector<std::function<void( const MouseMoveEvent& )>> mouseMoveListeners;
	std::vector<std::function<void( const MouseScrollEvent& )>> mouseScrollListeners;

	/**
	 * @brief Dispatches a KeyEvent to all registered key listeners.
	 * @param event The KeyEvent to dispatch.
	 */
	void dispatch( const KeyEvent& event ) {
		for ( const auto& listener : keyListeners ) {
			listener( event );
		}
	}

	/**
	 * @brief Dispatches a MouseButtonEvent to all registered mouse button listeners.
	 * @param event The MouseButtonEvent to dispatch.
	 */
	void dispatch( const MouseButtonEvent& event ) {
		for ( const auto& listener : mouseButtonListeners ) {
			listener( event );
		}
	}

	/**
	 * @brief Dispatches a MouseMoveEvent to all registered mouse move listeners.
	 * @param event The MouseMoveEvent to dispatch.
	 */
	void dispatch( const MouseMoveEvent& event ) {
		for ( const auto& listener : mouseMoveListeners ) {
			listener( event );
		}
	}

	/**
	 * @brief Dispatches a MouseScrollEvent to all registered mouse scroll listeners.
	 * @param event The MouseScrollEvent to dispatch.
	 */
	void dispatch( const MouseScrollEvent& event ) {
		for ( const auto& listener : mouseScrollListeners ) {
			listener( event );
		}
	}
};

/**
 * @brief Manages all input from keyboard and mouse.
 *
 * This class implements the Singleton design pattern. It provides methods
 * to query the state of keys and mouse buttons, get mouse position and deltas,
 * and access an EventDispatcher for event-based input.
 */
class InputManager
{
public:
	/**
	 * @brief Gets the singleton instance of the InputManager.
	 * @return A reference to the single InputManager instance.
	 */
	static InputManager& getInstance(); // Singleton access method.

	/**
	 * @brief Initializes the InputManager with the given GLFW window.
	 *
	 * Sets up GLFW callbacks for keyboard, mouse position, mouse buttons, and scroll.
	 * Initializes key and mouse button states to false.
	 * @param window A pointer to the GLFWwindow.
	 */
	void init( GLFWwindow* window );
	/**
	 * @brief Updates the input states.
	 *
	 * This should be called once per frame. It copies current states to last states
	 * for 'just pressed/released' logic and resets scroll offsets.
	 */
	void update();

	/**
	 * @brief Checks if a specific key is currently pressed.
	 * @param keyCode The GLFW key code (e.g., GLFW_KEY_SPACE).
	 * @return True if the key is pressed, false otherwise.
	 */
	bool isKeyPressed( int keyCode ) const;
	/**
	 * @brief Checks if a specific key was just pressed in the current frame.
	 * @param keyCode The GLFW key code.
	 * @return True if the key was pressed in this frame but not in the previous, false otherwise.
	 */
	bool isKeyJustPressed( int keyCode ) const;
	/**
	 * @brief Checks if a specific key was just released in the current frame.
	 * @param keyCode The GLFW key code.
	 * @return True if the key was released in this frame but was pressed in the previous, false otherwise.
	 */
	bool isKeyJustReleased( int keyCode ) const;

	/**
	 * @brief Checks if a specific mouse button is currently pressed.
	 * @param button The GLFW mouse button code (e.g., GLFW_MOUSE_BUTTON_LEFT).
	 * @return True if the button is pressed, false otherwise.
	 */
	bool isMouseButtonPressed( int button ) const;
	/**
	 * @brief Checks if a specific mouse button was just pressed in the current frame.
	 * @param button The GLFW mouse button code.
	 * @return True if the button was pressed in this frame but not in the previous, false otherwise.
	 */
	bool isMouseButtonJustPressed( int button ) const;
	/**
	 * @brief Checks if a specific mouse button was just released in the current frame.
	 * @param button The GLFW mouse button code.
	 * @return True if the button was released in this frame but was pressed in the previous, false otherwise.
	 */
	bool isMouseButtonJustReleased( int button ) const;

	/**
	 * @brief Gets the current mouse cursor position.
	 * @return A glm::vec2 representing the X and Y coordinates of the mouse.
	 */
	glm::vec2 getMousePosition() const;
	/**
	 * @brief Gets the change in mouse cursor position since the last frame.
	 * @return A glm::vec2 representing the X and Y deltas.
	 */
	glm::vec2 getMouseDelta() const;
	/**
	 * @brief Gets the scroll offset for the current frame.
	 * @return A glm::vec2 representing the X and Y scroll offsets.
	 */
	glm::vec2 getScrollOffset() const;

	/**
	 * @brief Checks if the mouse is currently being dragged (any mouse button is pressed while moving).
	 * @return True if any mouse button is pressed and the mouse is moving, false otherwise.
	 */
	bool isMouseDragging() const;

	/**
	 * @brief Gets the EventDispatcher instance to register event listeners.
	 * @return A reference to the EventDispatcher.
	 */
	EventDispatcher& getEventDispatcher() { return dispatcher; }

private:
	static InputManager instance; // The single instance of the InputManager class, implementing the Singleton pattern.

	/**
	 * @brief Private constructor to enforce Singleton pattern.
	 *
	 * Initializes mouse coordinates and scroll offsets to zero, and mouseDragging to false.
	 */
	InputManager(); // Private constructor for singleton.
	/**
	 * @brief Default destructor.
	 */
	~InputManager() = default;
	InputManager( const InputManager& ) = delete; // Delete copy constructor to prevent copying.
	InputManager& operator=( const InputManager& ) = delete; // Delete assignment operator to prevent assignment.

	std::map<int, bool> currentKeyStates; // Current state of each key (pressed/not pressed).
	std::map<int, bool> lastKeyStates; // State of each key in the previous frame.
	std::map<int, bool> currentMouseButtonStates; // Current state of each mouse button.
	std::map<int, bool> lastMouseButtonStates; // State of each mouse button in the previous frame.

	double currentMouseX, currentMouseY; // Current mouse cursor position.
	double lastMouseX, lastMouseY; // Mouse cursor position in the previous frame.
	double scrollXOffset, scrollYOffset; // Scroll wheel offset for the current frame.
	bool mouseDragging; // True if a mouse button is held down while moving.

	EventDispatcher dispatcher; // Event dispatcher for sending input events.

	// Static GLFW callback functions. These are static as GLFW requires them to be global or static member functions.
	/**
	 * @brief Static callback function for GLFW keyboard events.
	 * @param window The GLFW window that received the event.
	 * @param key The keyboard key that was pressed or released.
	 * @param scancode The system-specific scancode of the key.
	 * @param action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
	 * @param mods Modifier flags.
	 */
	static void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
	/**
	 * @brief Static callback function for GLFW cursor position events.
	 * @param window The GLFW window that received the event.
	 * @param xPos The new X-coordinate of the cursor.
	 * @param yPos The new Y-coordinate of the cursor.
	 */
	static void glfwCursorPosCallback( GLFWwindow* window, double xPos, double yPos );
	/**
	 * @brief Static callback function for GLFW mouse button events.
	 * @param window The GLFW window that received the event.
	 * @param button The mouse button that was pressed or released.
	 * @param action The action (GLFW_PRESS, GLFW_RELEASE).
	 * @param mods Modifier flags.
	 */
	static void glfwMouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
	/**
	 * @brief Static callback function for GLFW scroll events.
	 * @param window The GLFW window that received the event.
	 * @param xOffset The scroll offset along the X axis.
	 * @param yOffset The scroll offset along the Y axis.
	 */
	static void glfwScrollCallback( GLFWwindow* window, double xOffset, double yOffset );
};