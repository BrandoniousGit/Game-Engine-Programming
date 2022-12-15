#include <gepEngine/gepEngine.h>
#include <iostream>

using namespace gepEngine;

struct Update : Component
{
	void OnInitialize()
	{
		GetEntity()->GetTransform()->SetPosition(vec3(0.0f, 1.5f, 0.0f));
	}

	void OnTick()
	{
		GetEntity()->GetTransform()->AddPosition(vec3(0.0f, -0.005f, 0.0f));
		GetEntity()->GetTransform()->AddRotation(vec3(0.0f, 5.0f, 0.0f));
	}
};

struct Update2 : Component
{
	void OnTick()
	{
		
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::Initialize();

	//Entity 1 ====================
	std::shared_ptr<Entity> e = core->AddEntity();
	e->AddComponent<Update>();
	e->AddComponent<ModelRenderer>();
	e->AddComponent<BoxCollider>();
	e->AddComponent<Rigidbody>();
	e->GetTransform()->SetScale(glm::vec3(0.01f));

	//std::shared_ptr<AudioSource> as = e->addComponent<AudioSource>();
	//as->setAudio(core->getResources()->load<Audio>("audio/horn"));
	//as->setLoop(true);

	//Entity 2 ====================
	std::shared_ptr<Entity> e2 = core->AddEntity();
	e2->AddComponent<Update2>();
	e2->AddComponent<TriangleRenderer>();
	e2->AddComponent<BoxCollider>();
	e2->AddComponent<Rigidbody>();

	core->Start();

	return 0;
}