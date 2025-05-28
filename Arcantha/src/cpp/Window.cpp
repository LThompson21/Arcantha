#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

static void glfwErrorCallback( int error, const char* description ) {
	std::cerr << "Err: " << description << std::endl;
}

Window::Window( int w, int h, glm::vec4 clear, const std::string& title, bool maximizeOnStart, bool resizeable ) :
	w( w ), h( h ), clear( clear ), title( title ), window( nullptr ), maximizeOnStart( maximizeOnStart ), resizeable( resizeable ) {}

void Window::Init() {
	if ( !glfwInit() ) {
		std::cerr << "Err: Failure to initialize GLFW." << std::endl;
		exit( -1 );
	}

	glfwSetErrorCallback( glfwErrorCallback );

	glfwDefaultWindowHints();
	glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
	glfwWindowHint( GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE );
	glfwWindowHint( GLFW_MAXIMIZED, maximizeOnStart ? GLFW_TRUE : GLFW_FALSE );

	this->window = glfwCreateWindow( w, h, title.c_str(), NULL, NULL );
	if ( !window ) {
		std::cerr << "Err: Failure to create GLFW window." << std::endl;
		exit( -2 );
	}

	glfwMakeContextCurrent( window );
	gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );

	glfwSwapInterval( 1 );

	glfwShowWindow( window );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Window::Update() {
	glfwPollEvents();

	glClearColor( clear.x, clear.y, clear.z, clear.w );
	glClear( GL_COLOR_BUFFER_BIT );

	glfwSwapBuffers( window );
}

void Window::Shutdown() {
	glfwDestroyWindow( window );
	glfwTerminate();
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose( window );
}