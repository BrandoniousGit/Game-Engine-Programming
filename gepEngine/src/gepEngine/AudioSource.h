#ifndef GEPENGINE_AUDIOSOURCE_H
#define GEPENGINE_AUDIOSOURCE_H

#include "component.h"
#include "AudioClip.h"
#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include "glmWrap.h"

namespace gepEngine
{
	struct AudioSource : Component
	{
		AudioSource();

		ALuint GetSourceId() { return m_sourceId; }

		void SetAudio();

		void PlaySound(AudioClip clip, ALfloat volume);

	private:
		ALuint m_sourceId; ///< The audio source Id
	};
}
#endif
