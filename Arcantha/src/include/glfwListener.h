#pragma once
#include <GLFW/glfw3.h>

namespace Callback
{
	void glfwError( int error, const char* description );
	void glfwWindowSize( GLFWwindow* window, int w, int h );
}

namespace Key
{
	static bool keyPressed[ GLFW_KEY_LAST + 1 ];

	void callback( GLFWwindow* window, int key, int scancode, int action, int mods );
	bool isPressed( int keyCode );
}

namespace Mouse
{
	static double scrollX, scrollY;
	static double xPos, yPos, lastY, lastX;
	static bool mouseButtonPressed[ GLFW_MOUSE_BUTTON_LAST + 1 ];
	static bool isDragging;

	void posCallback( GLFWwindow* window, double xPos, double yPos );
	void buttonCallback( GLFWwindow* window, int button, int action, int mods );
	void scrollCallback( GLFWwindow* window, double xOffset, double yOffset );
}