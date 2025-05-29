#include <iostream> // Required for basic input/output operations, though not used directly in this main.
#include "Application.h" // Includes the Application class definition, which contains the main program logic.

/**
 * @brief The main entry point of the application.
 *
 * This function gets the singleton instance of the Application class and
 * calls its `run` method to start the application lifecycle.
 * @return 0 if the application exits successfully.
 */
int main() {
	Application& app = Application::getInstance(); // Get the singleton instance of the Application.
	app.run(); // Run the application, which includes initialization, main loop, and shutdown.
}