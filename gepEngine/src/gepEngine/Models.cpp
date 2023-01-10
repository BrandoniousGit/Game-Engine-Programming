#include "Models.h"

namespace gepEngine
{
	void Models::load_model(const std::string _path)
	{
		m_model = new rend::Model(_path.c_str());
	}

	void Models::OnLoad()
	{
		load_model(GetPath());
	}
}