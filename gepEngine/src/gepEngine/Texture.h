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
	struct MeshRenderer;
	struct Texture : Resource
	{
		/**
		 * @brief Loads a texture from the cache
		 * @param _path 
		*/
		void load_texture(const std::string _path);

		void OnLoad();

	private:
		friend MeshRenderer;
		std::shared_ptr<rend::Texture> m_texture;
	};
}
#endif