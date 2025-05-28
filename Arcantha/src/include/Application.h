#pragma once

#include <string>

#include "Window.h"

class Application
{
public:
	static Application& Get();
	void Run();

private:
	static Application instance;

	Window& mainWindow;

	Application();
	~Application() = default;

	void Init();
	void Loop();
	void Shutdown();

	void Update( double dt );
};