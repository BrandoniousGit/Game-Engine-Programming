#include "component.h"

namespace gepEngine
{
	void Component::onTick() {}
	void Component::onDisplay() {}

	void Component::tick()
	{
		onTick();
	}

	void Component::display()
	{
		onDisplay();
	}
}