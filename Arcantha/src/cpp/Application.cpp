#include "Application.h"
#include "Window.h"
#include <string>

Application Application::instance;

Application::Application()
	: mainWindow( *( new Window( 1920, 1080, glm::vec4( 1, 1, 1, 1 ), "Arcantha", true, true ) ) ) {}

Application& Application::Get() {
	return instance;
}

void Application::Run() {
	Init();
	Loop();
	Shutdown();
}

void Application::Init() {
	mainWindow.Init();
}

void Application::Loop() {
	double dt = -1;
	double frameBegin = glfwGetTime();
	double frameEnd;

	while ( !mainWindow.ShouldClose() ) {
		Update(dt);

		frameEnd = glfwGetTime();
		dt = frameEnd - frameBegin;
		frameBegin = frameEnd;
	}
}

void Application::Shutdown() {
	mainWindow.Shutdown();
};

void Application::Update( double dt ) {
	if ( dt <= 0 ) return;

	mainWindow.Update();
}