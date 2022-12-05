#include "component.h"
#include "entity.h"

namespace gepEngine
{
	void Component::OnTick() {}
	void Component::OnDisplay() {}
	void Component::OnInitialize() {}

	void Component::Tick()
	{
		OnTick();
	}

	void Component::Display()
	{
		OnDisplay();
	}

	void Component::Initialize()
	{
		OnInitialize();
	}

	std::shared_ptr<Entity> Component::GetEntity() const
	{
		return m_entity.lock();
	}
}