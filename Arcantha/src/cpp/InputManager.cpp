#include "InputManager.h"
#include <iostream>

InputManager InputManager::instance;

InputManager& InputManager::getInstance() {
	return instance;
}

InputManager::InputManager()
	: currentMouseX( 0.0 ), currentMouseY( 0.0 ), lastMouseX( 0.0 ), lastMouseY( 0.0 ),
	scrollXOffset( 0.0 ), scrollYOffset( 0.0 ), mouseDragging( false ) {}

void InputManager::init( GLFWwindow* window ) {
	glfwSetKeyCallback( window, InputManager::glfwKeyCallback );
	glfwSetCursorPosCallback( window, InputManager::glfwCursorPosCallback );
	glfwSetMouseButtonCallback( window, InputManager::glfwMouseButtonCallback );
	glfwSetScrollCallback( window, InputManager::glfwScrollCallback );

	// Initialize all keys/buttons to not pressed
	for ( int i = 0; i <= GLFW_KEY_LAST; ++i ) {
		currentKeyStates[ i ] = false;
		lastKeyStates[ i ] = false;
	}
	for ( int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i ) {
		currentMouseButtonStates[ i ] = false;
		lastMouseButtonStates[ i ] = false;
	}
}

void InputManager::update() {
	// Copy current states to last states for 'just pressed/released' logic
	lastKeyStates = currentKeyStates;
	lastMouseButtonStates = currentMouseButtonStates;

	// Reset scroll offset each frame as it's incremental
	scrollXOffset = 0.0;
	scrollYOffset = 0.0;

	// Calculate mouse delta
	InputManager::getInstance().lastMouseX = InputManager::getInstance().currentMouseX;
	InputManager::getInstance().lastMouseY = InputManager::getInstance().currentMouseY;
}

bool InputManager::isKeyPressed( int keyCode ) const {
	auto it = currentKeyStates.find( keyCode );
	return it != currentKeyStates.end() && it->second;
}

bool InputManager::isKeyJustPressed( int keyCode ) const {
	return isKeyPressed( keyCode ) && !lastKeyStates.at( keyCode );
}

bool InputManager::isKeyJustReleased( int keyCode ) const {
	return !isKeyPressed( keyCode ) && lastKeyStates.at( keyCode );
}

bool InputManager::isMouseButtonPressed( int button ) const {
	auto it = currentMouseButtonStates.find( button );
	return it != currentMouseButtonStates.end() && it->second;
}

bool InputManager::isMouseButtonJustPressed( int button ) const {
	return isMouseButtonPressed( button ) && !lastMouseButtonStates.at( button );
}

bool InputManager::isMouseButtonJustReleased( int button ) const {
	return !isMouseButtonPressed( button ) && lastMouseButtonStates.at( button );
}

glm::vec2 InputManager::getMousePosition() const {
	return glm::vec2( currentMouseX, currentMouseY );
}

glm::vec2 InputManager::getMouseDelta() const {
	return glm::vec2( currentMouseX - lastMouseX, currentMouseY - lastMouseY );
}

glm::vec2 InputManager::getScrollOffset() const {
	return glm::vec2( scrollXOffset, scrollYOffset );
}

bool InputManager::isMouseDragging() const {
	return mouseDragging;
}

// Static GLFW callbacks
void InputManager::glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if ( key >= 0 && key <= GLFW_KEY_LAST ) {
		InputManager::getInstance().currentKeyStates[ key ] = ( action == GLFW_PRESS || action == GLFW_REPEAT );
		InputManager::getInstance().dispatcher.dispatch( KeyEvent{ key, scancode, action, mods } );
	}
}

void InputManager::glfwCursorPosCallback( GLFWwindow* window, double xPos, double yPos ) {
	InputManager::getInstance().currentMouseX = xPos;
	InputManager::getInstance().currentMouseY = yPos;

	// Update dragging state based on mouse buttons
	bool anyButtonDown = false;
	for ( int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i ) {
		if ( InputManager::getInstance().currentMouseButtonStates[ i ] ) {
			anyButtonDown = true;
			break;
		}
	}
	InputManager::getInstance().mouseDragging = anyButtonDown;

	InputManager::getInstance().dispatcher.dispatch( MouseMoveEvent{ xPos, yPos,
		xPos - InputManager::getInstance().lastMouseX, yPos - InputManager::getInstance().lastMouseY } );
}

void InputManager::glfwMouseButtonCallback( GLFWwindow* window, int button, int action, int mods ) {
	if ( button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST ) {
		InputManager::getInstance().currentMouseButtonStates[ button ] = ( action == GLFW_PRESS );
		InputManager::getInstance().mouseDragging = InputManager::getInstance().isMouseButtonPressed( 0 ) ||
			InputManager::getInstance().isMouseButtonPressed( 1 ) ||
			InputManager::getInstance().isMouseButtonPressed( 2 ); // Or any other button
		InputManager::getInstance().dispatcher.dispatch( { button, action, mods,
			InputManager::getInstance().currentMouseX, InputManager::getInstance().currentMouseY } );
	}
}

void InputManager::glfwScrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {
	InputManager::getInstance().scrollXOffset = xOffset;
	InputManager::getInstance().scrollYOffset = yOffset;
	InputManager::getInstance().dispatcher.dispatch( MouseScrollEvent{ xOffset, yOffset } );
}