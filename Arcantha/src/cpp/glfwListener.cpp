#include "glfwListener.h"
#include "Window.h"
#include "glad/glad.h"
#include <iostream>

void Callback::glfwError( int error, const char* description ) {
	std::cerr << "Err: " << error << " | " << description << std::endl;
}

void Callback::glfwWindowSize( GLFWwindow* window, int w, int h ) {
	Window* windowInstance = static_cast< Window* >( glfwGetWindowUserPointer( window ) );
	if ( windowInstance ) {
		windowInstance->setWidth( w );
		windowInstance->setHeight( h );

		glViewport( 0, 0, w, h );
	}
}

void Key::callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if ( action == GLFW_PRESS ) {
		keyPressed[ key ] = true;
	}
	else if ( action == GLFW_RELEASE ) {
		keyPressed[ key ] = false;
	}
}

bool Key::isPressed( int keyCode ) {
	return keyPressed[ keyCode ];
}

void Mouse::posCallback( GLFWwindow* window, double xPos, double yPos ) {
	lastX = xPos;
	lastY = yPos;

	Mouse::xPos = xPos;
	Mouse::yPos = yPos;

	isDragging = mouseButtonPressed[ 0 ] || mouseButtonPressed[ 1 ] || mouseButtonPressed[ 2 ];
}

void Mouse::buttonCallback( GLFWwindow* window, int button, int action, int mods ) {
	if ( action == GLFW_PRESS ) {
		if ( button <= GLFW_MOUSE_BUTTON_LAST ) {
			*( mouseButtonPressed + button ) = true;
		}
	}
	else if ( action == GLFW_RELEASE ) {
		if ( button <= GLFW_MOUSE_BUTTON_LAST ) {
			*( mouseButtonPressed + button ) = false;
			isDragging = false;
		}
	}
}

void Mouse::scrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {
	scrollX = xOffset;
	scrollY = yOffset;
}