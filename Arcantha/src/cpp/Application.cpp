#include "Application.h"
#include "Window.h"
#include <string>

Application Application::instance;

Application::Application() :
	mainWindow( *( new Window( 800, 600, glm::vec4( .75, .5, 1, 1 ), "Arcantha", false, true ) ) ) {}

Application& Application::get() {
	return instance;
}

void Application::run() {
	init();
	loop();
	shutdown();
}

void Application::init() {
	mainWindow.init();
}

void Application::loop() {
	double dt = -1;
	double frameBegin = glfwGetTime();
	double frameEnd;

	while ( !mainWindow.shouldClose() ) {
		update( dt );

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
}