#pragma once

#include <string>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window( int width, int height, glm::vec4 clear, const std::string& title, bool maximizeOnStart, bool resizeable );
	~Window() = default;

	void init();
	void update();
	void shutdown();

	bool shouldClose();

	int getWidth() const;
	int getHeight() const;

	void setWidth( const int width );
	void setHeight( const int height );

private:
	GLFWwindow* window;
	int width, height;
	glm::vec4 clear;
	const std::string title;
	bool maximizeOnStart, resizeable;
};