#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

int main()
{
	ALCdevice* device = alcOpenDevice( NULL ); // Select the default device
	if ( !device )
	{
		std::cerr << "Failed to open OpenAL device!" << std::endl;
		return 1;
	}
	std::cout << "OpenAL device opened successfully." << std::endl;

	ALCcontext* context = alcCreateContext( device, NULL );
	if ( !context )
	{
		std::cerr << "Failed to create OpenAL context!" << std::endl;
		alcCloseDevice( device );
		return 1;
	}
	std::cout << "OpenAL context created successfully." << std::endl;

	if ( !alcMakeContextCurrent( context ) )
	{
		std::cerr << "Failed to make OpenAL context current!" << std::endl;
		alcDestroyContext( context );
		alcCloseDevice( device );
		return 1;
	}
	std::cout << "OpenAL context made current." << std::endl;

	// Simple check for OpenAL error
	ALenum error = alGetError();
	if ( error != AL_NO_ERROR )
	{
		std::cerr << "OpenAL error after context setup: " << error << std::endl;
	}

	alcMakeContextCurrent( NULL ); // Detach context
	alcDestroyContext( context );
	std::cout << "OpenAL context destroyed." << std::endl;

	alcCloseDevice( device );
	std::cout << "OpenAL device closed." << std::endl;
	return 0;
}
