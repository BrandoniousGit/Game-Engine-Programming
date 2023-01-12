#ifndef GEPENGINE_AUDIOCLIP_H
#define GEPENGINE_AUDIOCLIP_H

#include "Resource.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>

namespace gepEngine
{
	struct AudioSource;

	struct AudioClip : Resource
	{
		/**
		 * @brief Gets the bufferId
		 * @return m_bufferId
		*/
		ALuint GetBufferId() { return m_bufferId; }

		/**
		 * @brief Loads an audio ogg file
		 * @param _path 
		 * @param _buffer 
		 * @param _format 
		 * @param _freq 
		*/
		static void load_ogg(const std::string& _path, std::vector<unsigned char>& _buffer,
			ALenum& _format, ALsizei& _freq);

		void OnLoad();

	private:
		ALenum m_format; //< Stored audio format 
		ALsizei m_freq; //< Stored audio frequency
		ALuint m_bufferId; //< Stored buffer Id
	};
}
#endif