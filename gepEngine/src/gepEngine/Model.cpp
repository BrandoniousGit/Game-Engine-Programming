#include "Model.h"

namespace gepEngine
{
	void Model::load_model(const std::string _path)
	{
		m_model = std::make_shared<rend::Model>(_path.c_str());
	}

	void Model::OnLoad()
	{
		load_model(GetPath());
	}
}