#include <iostream>
#include "Application.h"

int main() {
	Application& app = Application::get();
	app.run();
}