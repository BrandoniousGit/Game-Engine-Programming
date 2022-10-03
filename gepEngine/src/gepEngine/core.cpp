#include "core.h"

namespace gepEngine
{

	Shared<Core> Core::initialize()
	{
		Shared<Core> rtn = std::make_shared<Core>();

		return rtn;
	}

}