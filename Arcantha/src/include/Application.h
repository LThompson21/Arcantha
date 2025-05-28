#pragma once

#include <string>

#include "Window.h"

class Application
{
public:
	static Application& get();
	void run();

private:
	static Application instance;

	Window& mainWindow;

	Application();
	~Application() = default;

	void init();
	void loop();
	void shutdown();

	void update( double dt );
};