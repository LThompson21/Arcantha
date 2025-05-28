#include <iostream>
#include "Application.h"

int main() {
	Application& app = Application::getInstance();
	app.run();
}