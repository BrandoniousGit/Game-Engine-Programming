#include "core.h"
#include "entity.h"

namespace gepEngine
{

	std::shared_ptr<Core> Core::initialize() //Engine core
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_running = false; //Initialising running bool because otherwise it's a garbage value

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity() //Function to add entity to scene
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		m_entities.push_back(rtn);

		return rtn;
	}

	void Core::start() //Runs once on engine start
	{
		m_running = true;

		while (m_running)
		{

		}
	}

	void Core::stop() //Runs once on engine quit
	{
		m_running = false;
	}
}