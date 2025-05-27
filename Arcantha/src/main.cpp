#include <iostream>
#include "Application.h"

int main() {
	std::cout << "Hello World!" << std::endl;

	Application& app = Application::Get();
	app.Run();

	return 0;
}