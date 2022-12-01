#include <gepEngine/gepEngine.h>
#include <iostream>

using namespace gepEngine;

void load_ogg(const std::string&, std::vector<unsigned char>&, ALenum&, ALsizei&);

struct Update : Component
{
	void OnTick()
	{
		getEntity()->getTransform()->addRotation(glm::vec3(1.0f, 1.0f, 1.5f));
	}
};
struct Update2 : Component
{
	void OnTick()
	{
		getEntity()->getTransform()->setPosition(glm::vec3(0, 1, 0));
		getEntity()->getTransform()->addRotation(glm::vec3(-1.0f, -1.0f, -1.5f));
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> e = core->addEntity();
	std::shared_ptr<Entity> e2 = core->addEntity();
	//std::shared_ptr<AudioSource> as = e->addComponent<AudioSource>();
	//as->setAudio(core->getResources()->load<Audio>("audio/horn"));
	//as->setLoop(true);
	e->addComponent<Update>();
	e->addComponent<TriangleRenderer>();
	e2->addComponent<Update2>();
	e2->addComponent<TriangleRenderer>();
	//e->addComponent<AudioSource>();

	core->start();

	return 0;
}