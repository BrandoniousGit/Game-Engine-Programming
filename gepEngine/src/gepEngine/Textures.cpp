#include "Textures.h"

namespace gepEngine
{
	void Textures::load_texture(const std::string _path)
	{
		m_texture = new rend::Texture(_path.c_str());
	}

	void Textures::OnLoad()
	{
		load_texture(GetPath());
	}
}