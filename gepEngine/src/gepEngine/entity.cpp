#include "Entity.h"
#include "Component.h"

namespace gepEngine
{

	void Entity::Tick() 
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Tick();
		}
	}

	void Entity::Display() 
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Display();
		}
	}

	std::shared_ptr<Transform> Entity::GetTransform()
	{
		return m_transform.lock();
	}

	std::shared_ptr<Core> Entity::GetCore()
	{
		return m_core.lock();
	}

	void Entity::Initialize()
	{
		for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Initialize();
		}
	}
}