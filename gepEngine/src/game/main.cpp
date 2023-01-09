#include <gepEngine/gepEngine.h>
#include <iostream>

#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()

using namespace gepEngine;

struct UpdateMaxwell : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, -0.3f, -5.0f));
	}

	void OnTick()
	{
		//transform->AddRotation(vec3(0.0f, 2.0f, 0.0f));
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

struct UpdateEvilMaxwell : Component
{

};

struct floor : Component
{

};

struct UpdateCamera : Component
{
	void OnTick()
	{
		//transform->AddPosition(vec3(0.0f, 0.0f, 0.0f));
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::Initialize();

	std::shared_ptr<AudioClip> funkyTown = core->GetCache()->load<AudioClip>("../resources/sounds/catloop.ogg");

	//Camera
	std::shared_ptr<Entity> camera = core->AddEntity();
	camera->AddComponent<Camera>();
	camera->GetComponent<Camera>()->SetMainCam(camera->GetComponent<Camera>());
	camera->AddComponent<UpdateCamera>();

	//Maxwell ====================
	std::shared_ptr<Entity> maxwell = core->AddEntity();
	maxwell->AddComponent<UpdateMaxwell>();
	maxwell->AddComponent<ModelRenderer>();

	maxwell->AddComponent<BoxCollider>();
	maxwell->AddComponent<Rigidbody>();

	maxwell->AddComponent<AudioSource>();
	maxwell->GetComponent<AudioSource>()->PlaySound(funkyTown, 1.0f);
	maxwell->GetTransform()->SetScale(glm::vec3(0.05f));

	//Evil Maxwell ====================
	std::shared_ptr<Entity> eMaxwell = core->AddEntity();
	eMaxwell->AddComponent<UpdateEvilMaxwell>();

	//Floor ====================
	std::shared_ptr<Entity> floor = core->AddEntity();
	floor->AddComponent<UpdateEvilMaxwell>();

	core->Start();

	return 0;
}