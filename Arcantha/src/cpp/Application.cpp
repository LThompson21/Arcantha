#include "Application.h"
#include "Window.h"
#include <string>

Application Application::instance;

Application::Application()
	: mainWindow( *( new Window( 1920, 1080, glm::vec4( 1, 1, 1, 1 ), "Arcantha" ) ) ) {}

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
	float dt = -1;
	long frameBegin = glfwGetTime();
	long frameEnd;

	while ( !mainWindow.ShouldClose() ) {
		
	}
}

void Application::Shutdown() {
	mainWindow.Shutdown();
};

void Application::Update(float dt) {
	if ( dt <= 0 ) return;

	mainWindow.Update();
}