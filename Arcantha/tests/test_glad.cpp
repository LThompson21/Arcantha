#include <glad/glad.h>
#include <GLFW/glfw3.h> // GLAD needs a context, so we use GLFW

#include <iostream>

int main()
{
	if ( !glfwInit() )
	{
		std::cerr << "Failed to initialize GLFW for GLAD test!" << std::endl;
		return 1;
	}

	// Create a dummy window for context
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE ); // Don't show the window

	GLFWwindow* window = glfwCreateWindow( 1, 1, "GLAD Test Context", NULL, NULL );
	if ( !window )
	{
		std::cerr << "Failed to create GLFW window for GLAD context!" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent( window );

	if ( !gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) )
	{
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		glfwDestroyWindow( window );
		glfwTerminate();
		return 1;
	}
	std::cout << "GLAD initialized successfully." << std::endl;

	// Check a basic OpenGL function
	std::cout << "OpenGL Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;

	glfwDestroyWindow( window );
	glfwTerminate();
	return 0;
}