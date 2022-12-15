#include <gepEngine/gepEngine.h>
#include <iostream>

#define transform GetEntity()->GetTransform()

using namespace gepEngine;

struct Update : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, -0.3f, -5.0f));
	}

	void OnTick()
	{
		transform->AddRotation(vec3(0.0f, 2.0f, 0.0f));
		/*if (GetKey(Keys::W))
		{
			std::cout << "W Pressed!";
			transform->AddPosition(vec3(0.0f, -0.005f, 0.0f));
			transform->AddRotation(vec3(0.0f, 5.0f, 0.0f));
		}*/
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

	//AudioClip clip;
	std::shared_ptr<AudioClip> clip = core->GetCache()->load<AudioClip>("../resources/funkytown.ogg");

	//Entity 1 ====================
	std::shared_ptr<Entity> e = core->AddEntity();
	e->AddComponent<Update>();
	e->AddComponent<ModelRenderer>();
	e->AddComponent<BoxCollider>();
	e->AddComponent<Rigidbody>();
	e->AddComponent<AudioSource>();
	e->GetComponent<AudioSource>()->PlaySound(clip, 1.0f);
	e->GetTransform()->SetScale(glm::vec3(0.05f));

	//std::shared_ptr<AudioSource> as = e->addComponent<AudioSource>();
	//as->setAudio(core->getResources()->load<Audio>("audio/horn"));
	//as->setLoop(true);

	//Entity 2 ====================
	//std::shared_ptr<Entity> e2 = core->AddEntity();
	//e2->AddComponent<Update2>();
	//e2->AddComponent<TriangleRenderer>();
	//e2->AddComponent<BoxCollider>();
	//e2->AddComponent<Rigidbody>();



	core->Start();

	return 0;
}