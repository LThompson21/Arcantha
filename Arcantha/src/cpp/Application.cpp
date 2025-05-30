#include "Application.h" // Includes the Application class definition.
#include "Input.h" // Includes the InputManager class definition for input handling.
#include "Window.h" // Includes the Window class definition for window management.
#include <string> // Standard library for string operations.
#include <iostream> // Standard library for console output (e.g., std::cout).
#include <GLFW/glfw3.h> // Includes GLFW for glfwGetTime().

Application Application::instance;

Application::Application() :
	mainWindow( 800, 600, glm::vec4( 1, 1, 1, 1 ), "Arcantha", false, true ),
	eventDispatcher( InputManager::getInstance().getEventDispatcher() ) {}

Application& Application::getInstance() {
	return instance;
}

void Application::run() {
	init();
	loop();
	shutdown();
}

void Application::init() {
	mainWindow.init();

	InputManager::getInstance().init( mainWindow.getGLFWwindow() );
}

void Application::loop() {
	double dt = -1;
	double frameBegin = glfwGetTime();
	double frameEnd;

	while ( !mainWindow.shouldClose() ) {
		glfwPollEvents();

		update( dt );
		InputManager::getInstance().update();

		frameEnd = glfwGetTime();
		dt = frameEnd - frameBegin;
		frameBegin = frameEnd;
	}
}

void Application::shutdown() {
	mainWindow.shutdown();

	glfwTerminate();
};

void Application::update( double dt ) {
	if ( dt <= 0 ) return;

	mainWindow.update();
}