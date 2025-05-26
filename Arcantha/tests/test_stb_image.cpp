#include <stb_image.h>
#include <iostream>
#include <string>

int main()
{
	// This test doesn't require an actual image file to exist,
	// just that the header compiles and the function call links.
	// If you want to test with a real image, replace "dummy_image.png"
	// with a path to an actual image file.
	const char* imagePath = "non_existent_image.png"; // Using a non-existent file for a minimal test

	int width, height, channels;
	unsigned char* data = stbi_load( imagePath, &width, &height, &channels, 0 );

	if ( data == NULL )
	{
		// This is expected for a non-existent file, so it's not an error for the test.
		std::cout << "stb_image: Successfully attempted to load image '" << imagePath << "'." << std::endl;
		std::cout << "Expected failure to load (image not found), which means the library is linked." << std::endl;
		std::cout << "Error reason (if any): " << stbi_failure_reason() << std::endl;
	}
	else
	{
		// If you used an actual image path and it loaded successfully
		std::cout << "stb_image: Successfully loaded image '" << imagePath << "'." << std::endl;
		std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;
		stbi_image_free( data ); // Free the loaded image data
	}

	std::cout << "stb_image test completed." << std::endl;
	return 0;
}
