#include <gepEngine/gepEngine.h>
#include <iostream>
using namespace gepEngine;

struct Transform : Component
{
	void OnTick()
	{
		std::cout << "Ticking.." << std::endl;
	}

	void Display()
	{
		std::cout << "Display.." << std::endl;
	}
};

int main()
{

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	e->addComponent<Transform>();

	core->start();

	return 0;
}