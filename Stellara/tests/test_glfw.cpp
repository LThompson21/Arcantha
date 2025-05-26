#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	if ( !glfwInit() )
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return 1;
	}
	std::cout << "GLFW initialized successfully." << std::endl;

	GLFWwindow* window = glfwCreateWindow( 100, 100, "Test GLFW", NULL, NULL );
	if ( !window )
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return 1;
	}
	std::cout << "GLFW window created successfully." << std::endl;

	glfwMakeContextCurrent( window );
	std::cout << "GLFW context made current." << std::endl;

	glfwDestroyWindow( window );
	std::cout << "GLFW window destroyed." << std::endl;

	glfwTerminate();
	std::cout << "GLFW terminated successfully." << std::endl;
	return 0;
}
