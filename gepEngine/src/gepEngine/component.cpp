#include "component.h"

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
}