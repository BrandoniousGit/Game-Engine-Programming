#include <gepEngine/gepEngine.h>
#include <iostream>

using namespace gepEngine;

void load_ogg(const std::string&, std::vector<unsigned char>&, ALenum&, ALsizei&);

int main()
{

	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	//std::shared_ptr<AudioSource> as = e->addComponent<AudioSource>();
	//as->setAudio(core->getResources()->load<Audio>("audio/horn"));
	//as->setLoop(true);
	
	e->addComponent<TriangleRenderer>();
	e->addComponent<AudioSource>();

	core->start();

	return 0;
}