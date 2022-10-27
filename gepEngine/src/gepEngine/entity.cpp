#include "entity.h"
#include "component.h"

namespace gepEngine
{
	void Entity::Tick() 
	{
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Tick();
		}
	}

	void Entity::Display() 
	{
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Display();
		}
	}

	void Entity::Initialize()
	{
		for (std::vector<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Initialize();
		}
	}
}