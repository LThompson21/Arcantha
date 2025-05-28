#include "Application.h"
#include "InputManager.h"
#include "Window.h"
#include <string>
#include <iostream>

Application Application::instance;

Application::Application() :
	mainWindow( 800, 600, glm::vec4( .75, .5, 1, 1 ), "Arcantha", false, true ) {}

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
};

void Application::update( double dt ) {
	if ( dt <= 0 ) return;

	mainWindow.update();

	std::cout << "isKeyJustPressed: " << InputManager::getInstance().isKeyJustPressed( GLFW_KEY_SPACE ) << std::endl;
	std::cout << "isKeyJustReleased: " << InputManager::getInstance().isKeyJustReleased( GLFW_KEY_SPACE ) << std::endl;
	std::cout << "isKeyPressed: " << InputManager::getInstance().isKeyPressed( GLFW_KEY_SPACE ) << std::endl;
}