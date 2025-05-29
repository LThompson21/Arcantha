#include "InputManager.h" // Includes the InputManager class definition.
#include <iostream> // Required for std::cout for debugging purposes.

InputManager InputManager::instance; // Definition and initialization of the static singleton instance.

/**
 * @brief Gets the singleton instance of the InputManager.
 * @return A reference to the single InputManager instance.
 */
InputManager& InputManager::getInstance() {
	return instance;
}

/**
 * @brief Private constructor for the InputManager class.
 *
 * Initializes all mouse coordinates and scroll offsets to 0.0, and sets `mouseDragging` to false.
 */
InputManager::InputManager()
	: currentMouseX( 0.0 ), currentMouseY( 0.0 ), lastMouseX( 0.0 ), lastMouseY( 0.0 ),
	scrollXOffset( 0.0 ), scrollYOffset( 0.0 ), mouseDragging( false ) {}

/**
 * @brief Initializes the InputManager with the given GLFW window.
 *
 * Sets up GLFW callbacks for keyboard, cursor position, mouse buttons, and scroll wheel events.
 * Also initializes the state of all possible keys and mouse buttons to `false`.
 * @param window A pointer to the GLFWwindow to which callbacks will be attached.
 */
void InputManager::init( GLFWwindow* window ) {
	glfwSetKeyCallback( window, InputManager::glfwKeyCallback ); // Set keyboard event callback.
	glfwSetCursorPosCallback( window, InputManager::glfwCursorPosCallback ); // Set cursor position event callback.
	glfwSetMouseButtonCallback( window, InputManager::glfwMouseButtonCallback ); // Set mouse button event callback.
	glfwSetScrollCallback( window, InputManager::glfwScrollCallback ); // Set scroll wheel event callback.

	// Initialize all key states to not pressed.
	for ( int i = 0; i <= GLFW_KEY_LAST; i++ ) {
		currentKeyStates[ i ] = false; // Current state.
		lastKeyStates[ i ] = false; // Last frame's state.
	}
	// Initialize all mouse button states to not pressed.
	for ( int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++ ) {
		currentMouseButtonStates[ i ] = false; // Current state.
		lastMouseButtonStates[ i ] = false; // Last frame's state.
	}
}

/**
 * @brief Updates the input states.
 *
 * This method should be called once per frame. It copies the `currentKeyStates` and
 * `currentMouseButtonStates` to their respective `last` counterparts for 'just pressed/released' logic.
 * It also resets the scroll offset and updates `lastMouseX/Y` for delta calculation.
 */
void InputManager::update() {
	// Copy current states to last states for 'just pressed/released' logic.
	lastKeyStates = currentKeyStates;
	lastMouseButtonStates = currentMouseButtonStates;

	// Reset scroll offset each frame as it's incremental.
	scrollXOffset = 0.0;
	scrollYOffset = 0.0;

	// Update last mouse position for delta calculation in the next frame.
	lastMouseX = currentMouseX;
	lastMouseY = currentMouseY;
}

/**
 * @brief Checks if a specific key is currently pressed.
 * @param keyCode The GLFW key code (e.g., GLFW_KEY_A).
 * @return True if the key is pressed, false otherwise.
 */
bool InputManager::isKeyPressed( int keyCode ) const {
	auto it = currentKeyStates.find( keyCode ); // Find the key in the map.
	return it != currentKeyStates.end() && it->second; // Return true if found and state is true.
}

/**
 * @brief Checks if a specific key was just pressed in the current frame.
 *
 * A key is "just pressed" if it's currently pressed but was not pressed in the previous frame.
 * @param keyCode The GLFW key code.
 * @return True if the key was just pressed, false otherwise.
 */
bool InputManager::isKeyJustPressed( int keyCode ) const {
	// Check if current state is pressed and last state was not pressed.
	return isKeyPressed( keyCode ) && !lastKeyStates.at( keyCode );
}

/**
 * @brief Checks if a specific key was just released in the current frame.
 *
 * A key is "just released" if it's currently not pressed but was pressed in the previous frame.
 * @param keyCode The GLFW key code.
 * @return True if the key was just released, false otherwise.
 */
bool InputManager::isKeyJustReleased( int keyCode ) const {
	// Check if current state is not pressed and last state was pressed.
	return !isKeyPressed( keyCode ) && lastKeyStates.at( keyCode );
}

/**
 * @brief Checks if a specific mouse button is currently pressed.
 * @param button The GLFW mouse button code (e.g., GLFW_MOUSE_BUTTON_LEFT).
 * @return True if the button is pressed, false otherwise.
 */
bool InputManager::isMouseButtonPressed( int button ) const {
	auto it = currentMouseButtonStates.find( button ); // Find the button in the map.
	return it != currentMouseButtonStates.end() && it->second; // Return true if found and state is true.
}

/**
 * @brief Checks if a specific mouse button was just pressed in the current frame.
 *
 * A button is "just pressed" if it's currently pressed but was not pressed in the previous frame.
 * @param button The GLFW mouse button code.
 * @return True if the button was just pressed, false otherwise.
 */
bool InputManager::isMouseButtonJustPressed( int button ) const {
	// Check if current state is pressed and last state was not pressed.
	return isMouseButtonPressed( button ) && !lastMouseButtonStates.at( button );
}

/**
 * @brief Checks if a specific mouse button was just released in the current frame.
 *
 * A button is "just released" if it's currently not pressed but was pressed in the previous frame.
 * @param button The GLFW mouse button code.
 * @return True if the button was just released, false otherwise.
 */
bool InputManager::isMouseButtonJustReleased( int button ) const {
	// Check if current state is not pressed and last state was pressed.
	return !isMouseButtonPressed( button ) && lastMouseButtonStates.at( button );
}

/**
 * @brief Gets the current mouse cursor position.
 * @return A glm::vec2 representing the X and Y coordinates of the mouse.
 */
glm::vec2 InputManager::getMousePosition() const {
	return glm::vec2( currentMouseX, currentMouseY );
}

/**
 * @brief Gets the change in mouse cursor position since the last frame.
 * @return A glm::vec2 representing the X and Y deltas.
 */
glm::vec2 InputManager::getMouseDelta() const {
	return glm::vec2( currentMouseX - lastMouseX, currentMouseY - lastMouseY );
}

/**
 * @brief Gets the scroll offset for the current frame.
 * @return A glm::vec2 representing the X and Y scroll offsets.
 */
glm::vec2 InputManager::getScrollOffset() const {
	return glm::vec2( scrollXOffset, scrollYOffset );
}

/**
 * @brief Checks if the mouse is currently being dragged.
 *
 * This is true if any mouse button is currently held down.
 * @return True if a mouse button is pressed, false otherwise.
 */
bool InputManager::isMouseDragging() const {
	return mouseDragging;
}

// Static GLFW callbacks. These functions update the InputManager's internal state
// and dispatch events to registered listeners.

/**
 * @brief Static callback function for GLFW keyboard events.
 *
 * Updates the `currentKeyStates` and dispatches a `KeyEvent` to listeners.
 * @param window The GLFW window that received the event.
 * @param key The keyboard key that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action The action (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
 * @param mods Modifier flags.
 */
void InputManager::glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if ( key >= 0 && key <= GLFW_KEY_LAST ) { // Ensure the key code is within the valid range.
		// Update the current state of the key. It's pressed if action is PRESS or REPEAT.
		InputManager::getInstance().currentKeyStates[ key ] = ( action == GLFW_PRESS || action == GLFW_REPEAT );

		// Dispatch a KeyEvent to all registered key listeners.
		InputManager::getInstance().dispatcher.dispatch( KeyEvent{ {}, key, scancode, action, mods } );
	}
}

/**
 * @brief Static callback function for GLFW cursor position events.
 *
 * Updates `currentMouseX` and `currentMouseY`, calculates `mouseDragging` state,
 * and dispatches a `MouseMoveEvent` to listeners.
 * @param window The GLFW window that received the event.
 * @param xPos The new X-coordinate of the cursor.
 * @param yPos The new Y-coordinate of the cursor.
 */
void InputManager::glfwCursorPosCallback( GLFWwindow* window, double xPos, double yPos ) {
	InputManager::getInstance().currentMouseX = xPos; // Update current mouse X position.
	InputManager::getInstance().currentMouseY = yPos; // Update current mouse Y position.

	// Update dragging state based on whether any mouse button is currently down.
	bool anyButtonDown = false;
	for ( int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++ ) {
		if ( InputManager::getInstance().currentMouseButtonStates[ i ] ) {
			anyButtonDown = true;
			break;
		}
	}
	InputManager::getInstance().mouseDragging = anyButtonDown; // Set mouseDragging flag.

	// Dispatch a MouseMoveEvent, including the calculated delta.
	InputManager::getInstance().dispatcher.dispatch( MouseMoveEvent{ {}, xPos, yPos,
		xPos - InputManager::getInstance().lastMouseX, yPos - InputManager::getInstance().lastMouseY } );
}

/**
 * @brief Static callback function for GLFW mouse button events.
 *
 * Updates `currentMouseButtonStates`, recalculates `mouseDragging` state,
 * and dispatches a `MouseButtonEvent` to listeners.
 * @param window The GLFW window that received the event.
 * @param button The mouse button that was pressed or released.
 * @param action The action (GLFW_PRESS, GLFW_RELEASE).
 * @param mods Modifier flags.
 */
void InputManager::glfwMouseButtonCallback( GLFWwindow* window, int button, int action, int mods ) {
	if ( button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST ) { // Ensure the button code is within valid range.
		// Update the current state of the mouse button. It's pressed if action is PRESS.
		InputManager::getInstance().currentMouseButtonStates[ button ] = ( action == GLFW_PRESS );

		// Recalculate mouseDragging state based on the state of the first three mouse buttons.
		InputManager::getInstance().mouseDragging = InputManager::getInstance().isMouseButtonPressed( 0 ) ||
			InputManager::getInstance().isMouseButtonPressed( 1 ) ||
			InputManager::getInstance().isMouseButtonPressed( 2 );

		// Dispatch a MouseButtonEvent, including current mouse position.
		InputManager::getInstance().dispatcher.dispatch( MouseButtonEvent{ {}, button, action, mods,
			InputManager::getInstance().currentMouseX, InputManager::getInstance().currentMouseY } );
	}
}

/**
 * @brief Static callback function for GLFW scroll events.
 *
 * Updates `scrollXOffset` and `scrollYOffset` and dispatches a `MouseScrollEvent` to listeners.
 * @param window The GLFW window that received the event.
 * @param xOffset The scroll offset along the X axis.
 * @param yOffset The scroll offset along the Y axis.
 */
void InputManager::glfwScrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {
	InputManager::getInstance().scrollXOffset = xOffset; // Update horizontal scroll offset.
	InputManager::getInstance().scrollYOffset = yOffset; // Update vertical scroll offset.

	// Dispatch a MouseScrollEvent.
	InputManager::getInstance().dispatcher.dispatch( MouseScrollEvent{ {}, xOffset, yOffset } );
}