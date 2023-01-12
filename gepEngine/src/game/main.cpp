#include <gepEngine/gepEngine.h>
#include <iostream>
#include <scripts/Scripts.h>

#define coreLoad core->GetCache()->load

using namespace gepEngine;

int main()
{
	std::shared_ptr<Core> core = Core::Initialize();

	std::shared_ptr<AudioClip> funkyTown = coreLoad<AudioClip>("../resources/sounds/funkytown.ogg");
	std::shared_ptr<AudioClip> catloop = coreLoad<AudioClip>("../resources/sounds/catloop.ogg");

	std::shared_ptr<Models> maxwellModel = coreLoad<Models>("../resources/models/Maxwell.obj");
	std::shared_ptr<Models> floorModel = coreLoad<Models>("../resources/models/Floor.obj");

	std::shared_ptr<Textures> maxwellTexture = coreLoad<Textures>("../resources/textures/Maxwell_Diffuse.bmp");
	std::shared_ptr<Textures> eMaxwellTexture = coreLoad<Textures>("../resources/textures/Evil_Maxwell.bmp");
	std::shared_ptr<Textures> floorTexture = coreLoad<Textures>("../resources/textures/Floor_Diffuse.bmp");
	//Camera ====================

	std::shared_ptr<Entity> camera = core->AddEntity("mainCamera");;
	camera->AddComponent<Camera>();
	camera->GetComponent<Camera>()->SetMainCam(camera->GetComponent<Camera>());
	camera->AddComponent<CameraScript>();

	//Maxwell ====================
	std::shared_ptr<Entity> maxwell = core->AddEntity("Maxwell");
	maxwell->AddComponent<PlayerScript>();
	maxwell->AddComponent<MeshRenderer>();
	maxwell->GetComponent<MeshRenderer>()->SetModel(maxwellModel);
	maxwell->GetComponent<MeshRenderer>()->SetTexture(maxwellTexture);

	maxwell->AddComponent<BoxCollider>();
	maxwell->AddComponent<Rigidbody>();

	maxwell->AddComponent<AudioSource>();
	//maxwell->GetComponent<AudioSource>()->PlaySound(catloop, 1.0f);

	//Evil Maxwell ====================
	std::shared_ptr<Entity> eMaxwell = core->AddEntity("Evil Maxwell");
	eMaxwell->AddComponent<EnemyScript>();
	eMaxwell->AddComponent<MeshRenderer>();
	eMaxwell->GetComponent<MeshRenderer>()->SetModel(maxwellModel);
	eMaxwell->GetComponent<MeshRenderer>()->SetTexture(eMaxwellTexture);

	//Floor ====================
	std::shared_ptr<Entity> floor = core->AddEntity("Floor");
	floor->AddComponent<FloorScript>();
	floor->AddComponent<MeshRenderer>();
	floor->GetComponent<MeshRenderer>()->SetModel(floorModel);
	floor->GetComponent<MeshRenderer>()->SetTexture(floorTexture);

	core->Start();

	return 0;
}