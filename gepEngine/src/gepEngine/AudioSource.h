#ifndef GEPENGINE_AUDIOSOURCE_H
#define GEPENGINE_AUDIOSOURCE_H

#include "Component.h"
#include "AudioClip.h"
#include <string>
#include <vector>
#include <memory>
#include <AL/al.h>
#include <AL/alc.h>
#include "GlmWrap.h"

namespace gepEngine
{
	struct AudioSource : Component
	{
		AudioSource();

		ALuint GetSourceId() { return m_sourceId; }

		void SetAudio();

		void PlaySound(std::shared_ptr<AudioClip> clip, ALfloat volume);

	private:
		ALuint m_sourceId; ///< The audio source Id
	};
}
#endif
