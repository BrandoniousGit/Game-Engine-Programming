#ifndef GEPENGINE_TEXTURE_H
#define GEPENGINE_TEXTURE_H

#include "Resource.h"
#include <rend/rend.h>
#include <memory>
#include <string>
#include <vector>

namespace gepEngine
{
	struct Texture : Resource
	{
		void OnLoad();

	private:
		std::shared_ptr<rend::Texture> m_texture;
	};
}
#endif