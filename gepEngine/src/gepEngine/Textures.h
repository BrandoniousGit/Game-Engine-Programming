#ifndef GEPENGINE_TEXTURES_H
#define GEPENGINE_TEXTURES_H

#include "Resource.h"
#include <iostream>
#include <rend/rend.h>
#include <vector>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>

namespace gepEngine
{
	struct Textures : Resource
	{
		rend::Texture* GetRendTexture() { return m_texture; }

		void load_texture(const std::string _path);

		void OnLoad();

	private:
		rend::Texture* m_texture;
	};
}
#endif