#pragma once

#include <string>

#include <glm/ext/vector_float4.hpp>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window( int w, int h, glm::vec4 clear, const std::string& title );
	~Window() = default;

	void Init();
	void Update();
	void Shutdown();

	bool ShouldClose();

private:
	GLFWwindow* window;
	int w, h;
	glm::vec4 clear;
	const std::string title;
};