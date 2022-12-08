#ifndef GEPENGINE_AUDIOCLIP_H
#define GEPENGINE_AUDIOCLIP_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>

namespace gepEngine
{
	struct AudioSource;

	struct AudioClip
	{
		AudioClip();

		ALuint GetBufferId() { return m_bufferId; }

		static void load_ogg(const std::string& _path, std::vector<unsigned char>& _buffer,
			ALenum& _format, ALsizei& _freq);

	private:
		ALenum m_format; //< Stored audio format 
		ALsizei m_freq; //< Stored audio frequency
		ALuint m_bufferId; //< Stored buffer Id
	};
}

#endif