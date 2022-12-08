#include "AudioSource.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "stb_vorbis.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace gepEngine
{
	AudioSource::AudioSource()
	{
		/*************************************************************************
		 * Preparing sound source
		 *************************************************************************/
		m_sourceId = 0;
		alGenSources(1, &m_sourceId);
	}

	void AudioSource::SetAudio()
	{

	}

	void AudioSource::PlaySound(AudioClip clip, ALfloat _volume)
	{
		//alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcef(m_sourceId, AL_PITCH, 2);
		alSourcef(m_sourceId, AL_GAIN, _volume);

		alSourcei(m_sourceId, AL_BUFFER, clip.GetBufferId());
		alSourcePlay(m_sourceId);
	}
}