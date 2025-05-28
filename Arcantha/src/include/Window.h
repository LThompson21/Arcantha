#pragma once

#include <string>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window( const int width, const int height, glm::vec4 clear, const std::string& title, bool maximizeOnStart, bool resizeable );
	~Window() = default;

	void init();
	void update();
	void shutdown();

	bool shouldClose() const;
	void setShouldClose(bool shouldClose);

	GLFWwindow* getGLFWwindow() const;
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