#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "glfwListener.h"

Window::Window( const int width, const int height, glm::vec4 clear, const std::string& title,
	bool maximizeOnStart, bool resizeable ) :
	width( width ), height( height ), clear( clear ), title( title ), window( nullptr ),
	maximizeOnStart( maximizeOnStart ), resizeable( resizeable ) {}

void Window::init() {
	glfwSetErrorCallback( []( int error, const char* description ) {
		std::cerr << "Err: " << error << " | " << description << std::endl;
	} );

	if ( !glfwInit() ) {
		std::cerr << "Err: Failure to initialize GLFW." << std::endl;
		exit( -1 );
	}

	glfwDefaultWindowHints();
	glfwWindowHint( GLFW_VISIBLE, GLFW_FALSE );
	glfwWindowHint( GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE );
	glfwWindowHint( GLFW_MAXIMIZED, maximizeOnStart ? GLFW_TRUE : GLFW_FALSE );

	this->window = glfwCreateWindow( this->width, this->height, this->title.c_str(), NULL, NULL );
	if ( !window ) {
		std::cerr << "Err: Failure to create GLFW window." << std::endl;
		exit( -2 );
	}
	glfwSetWindowUserPointer( this->window, this );

	glfwSetWindowSizeCallback( this->window, []( GLFWwindow* window, int w, int h ) {
		Window* windowInstance = static_cast< Window* >( glfwGetWindowUserPointer( window ) );
		if ( windowInstance ) {
			windowInstance->setWidth( w );
			windowInstance->setHeight( h );

			glViewport( 0, 0, w, h );
		}
	} );

	glfwMakeContextCurrent( window );
	gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );

	glfwSwapInterval( 1 );

	glfwShowWindow( window );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Window::update() {
	glClearColor( clear.x, clear.y, clear.z, clear.w );
	glClear( GL_COLOR_BUFFER_BIT );

	glfwSwapBuffers( window );
}

void Window::shutdown() {
	glfwDestroyWindow( window );
	glfwTerminate();
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose( window );
}

void Window::setShouldClose( bool close ) {
	glfwSetWindowShouldClose( window, close );
}

GLFWwindow* Window::getGLFWwindow() const {
	return this->window;
}

int Window::getWidth() const {
	return this->width;
}

int Window::getHeight() const {
	return this->height;
}

void Window::setWidth( const int width ) {
	this->width = width;
}

void Window::setHeight( const int height ) {
	this->height = height;
}