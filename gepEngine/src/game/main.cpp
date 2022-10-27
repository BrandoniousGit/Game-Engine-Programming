#include <gepEngine/gepEngine.h>
#include <iostream>

using namespace gepEngine;

struct Transform : Component
{
	void OnTick()
	{

	}

	void OnDisplay()
	{

	}
};

int main()
{

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();

	e->addComponent<Transform>();
	e->addComponent<TriangleRenderer>();

	core->start();

	return 0;
}