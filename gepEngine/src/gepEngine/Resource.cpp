#include "Resource.h"

namespace gepEngine
{
	std::string Resource::GetPath() const
	{
		return m_path;
	}

	void Resource::Load()
	{
		OnLoad();
	}
}