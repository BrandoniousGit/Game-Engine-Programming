#include "Model.h"

namespace gepEngine
{
	void Model::load_model(const std::string& _path)
	{

	}

	void Model::OnLoad()
	{
		load_model(GetPath());
	}
}