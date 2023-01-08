#include <gepEngine/gepEngine.h>
#include <iostream>

#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()

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
		if (input->GetKey(Keys::W))
		{
			transform->AddPosition(vec3(0.0f, 0.05f, 0.0f));
		}
		if (input->GetKey(Keys::S))
		{
			transform->AddPosition(vec3(0.0f, -0.05f, 0.0f));
		}
		if (input->GetKey(Keys::A))
		{
			transform->AddPosition(vec3(-0.05f, 0.0f, 0.0f));
		}
		if (input->GetKey(Keys::D))
		{
			transform->AddPosition(vec3(0.05f, 0.0f, 0.0f));
		}
		if (input->GetKey(Keys::Q))
		{
			transform->AddPosition(vec3(0.0f, 0.0f, -0.05f));
		}
		if (input->GetKey(Keys::E))
		{
			transform->AddPosition(vec3(0.0f, 0.0f, 0.05f));
		}
	}
};

struct Update2 : Component
{
	void OnTick()
	{
		
	}
};

struct CameraUpdate : Component
{
	void OnTick()
	{
		//transform->AddPosition(vec3(0.0f, 0.0f, 0.0f));
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::Initialize();

	//AudioClip clip;
	std::shared_ptr<AudioClip> funkyTown = core->GetCache()->load<AudioClip>("../resources/sounds/catloop.ogg");

	//Camera
	std::shared_ptr<Entity> camera = core->AddEntity();
	camera->AddComponent<Camera>();
	camera->GetComponent<Camera>()->SetMainCam(camera->GetComponent<Camera>());
	camera->AddComponent<CameraUpdate>();

	//Entity 1 ====================
	std::shared_ptr<Entity> e = core->AddEntity();
	e->AddComponent<Update>();
	e->AddComponent<ModelRenderer>();
	e->AddComponent<BoxCollider>();
	e->AddComponent<Rigidbody>();
	e->AddComponent<AudioSource>();
	e->GetComponent<AudioSource>()->PlaySound(funkyTown, 1.0f);
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