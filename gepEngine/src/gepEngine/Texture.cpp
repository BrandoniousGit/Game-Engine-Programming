#include "Texture.h"

namespace gepEngine
{
	void Texture::load_texture(const std::string _path)
	{
		m_texture = std::make_shared<rend::Texture>(_path.c_str());
	}

	void Texture::OnLoad()
	{
		load_texture(GetPath());
	}
}