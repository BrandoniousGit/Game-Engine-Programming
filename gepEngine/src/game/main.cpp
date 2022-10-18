#include <gepEngine/gepEngine.h>
#include <iostream>
using namespace gepEngine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	//e->addComponent<Player>();

	core->start();

	return 0;
}