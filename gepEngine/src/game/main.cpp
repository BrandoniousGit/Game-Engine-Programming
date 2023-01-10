#include <gepEngine/gepEngine.h>
#include <iostream>

#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define coreLoad core->GetCache()->load

using namespace gepEngine;

struct UpdateMaxwell : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, -0.3f, -5.0f));
		transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
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
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, 0.3f, -3.0f));
		transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	}

	void OnTick()
	{

	}
};

struct UpdateFloor : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, 0.0f, 0.0f));
		transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	}

	void OnTick()
	{

	}
};

struct UpdateCamera : Component
{
	void OnTick()
	{
		transform->AddRotation(vec3(input->GetMousePos().x, 0.0f, 0.0f));
	}
};

int main()
{
	std::shared_ptr<Core> core = Core::Initialize();

	std::shared_ptr<AudioClip> funkyTown = coreLoad<AudioClip>("../resources/sounds/catloop.ogg");
	std::shared_ptr<Models> maxwellModel = coreLoad<Models>("../resources/models/Maxwell.obj");
	std::shared_ptr<Models> floorModel = coreLoad<Models>("../resources/models/Floor.obj");

	std::shared_ptr<Textures> maxwellTexture = coreLoad<Textures>("../resources/textures/Maxwell_Diffuse.bmp");
	std::shared_ptr<Textures> eMaxwellTexture = coreLoad<Textures>("../resources/textures/Evil_Maxwell.bmp");
	std::shared_ptr<Textures> floorTexture = coreLoad<Textures>("../resources/textures/Floor_Diffuse.bmp");

	//Camera
	std::shared_ptr<Entity> camera = core->AddEntity();
	camera->AddComponent<Camera>();
	camera->GetComponent<Camera>()->SetMainCam(camera->GetComponent<Camera>());
	camera->AddComponent<UpdateCamera>();

	//Maxwell ====================
	std::shared_ptr<Entity> maxwell = core->AddEntity();
	maxwell->AddComponent<UpdateMaxwell>();
	maxwell->AddComponent<MeshRenderer>();
	maxwell->GetComponent<MeshRenderer>()->SetModel(maxwellModel);
	maxwell->GetComponent<MeshRenderer>()->SetTexture(maxwellTexture);

	maxwell->AddComponent<BoxCollider>();
	maxwell->AddComponent<Rigidbody>();

	maxwell->AddComponent<AudioSource>();
	maxwell->GetComponent<AudioSource>()->PlaySound(funkyTown, 1.0f);

	//Evil Maxwell ====================
	std::shared_ptr<Entity> eMaxwell = core->AddEntity();
	eMaxwell->AddComponent<UpdateEvilMaxwell>();
	eMaxwell->AddComponent<MeshRenderer>();
	eMaxwell->GetComponent<MeshRenderer>()->SetModel(maxwellModel);
	eMaxwell->GetComponent<MeshRenderer>()->SetTexture(eMaxwellTexture);

	//Floor ====================
	std::shared_ptr<Entity> floor = core->AddEntity();
	floor->AddComponent<UpdateFloor>();
	floor->AddComponent<MeshRenderer>();
	floor->GetComponent<MeshRenderer>()->SetModel(floorModel);
	floor->GetComponent<MeshRenderer>()->SetTexture(floorTexture);

	core->Start();

	return 0;
}