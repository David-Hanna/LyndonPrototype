#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------
// MusicPlayer
//
// Encapsulates all things music (not sound effects!)
//--------------------------------------------------------------------------------------------------------------------------------------
#include <string>
#include <assert.h>

// library selection
#define SFML_AUDIO			// Windows, Mac OSX, Linux

#ifdef SFML_AUDIO
	#include <SFML\Audio.hpp>
#endif

namespace HE
{
	class MusicPlayer
	{
		// instance of library object
#ifdef SFML_AUDIO
		sf::Music sfMusic;
#endif

		// interface
	public:
		// construction and destruction
		// DH: Only one MusicPlayer may be instantiated at a time in the program.
		MusicPlayer() { static bool bInstantiated; assert(!bInstantiated && "Only one MusicPlayer may be instantiated at a time!"); bInstantiated = true; }
		~MusicPlayer() { static bool bInstantiated = false; };

		// music controls
		bool OpenFromFile(const std::string& fileName);
		bool OpenFromMemory(const void* data, std::size_t sizeInBytes);

		void SetVolume(float volume);
		void SetLooping(bool looping);
		void SetPitch(float pitch);

		float GetVolume() const;
		bool GetLooping() const;
		float GetPitch() const;					// pitch factor, ie 1.2
		unsigned int GetChannelCount() const;	// 1 for mono, 2 for stereo, etc
		unsigned int GetSampleRate() const;		// higher number = better quality

		void Play();
		void Pause();
		void Resume();
		void Stop();
	};
}