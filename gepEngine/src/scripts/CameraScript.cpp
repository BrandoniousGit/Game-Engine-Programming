#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()

using namespace gepEngine;

struct CameraScript : Component
{
	std::shared_ptr<Entity> player;
	vec3 offset;

	void OnInitialize()
	{
		//transform->SetRotation(vec3(-90, 0, 0));
		//transform->SetPosition(vec3(0, 0, 30));
		offset = vec3(0, 0, 5.0f);
		player = getCore->GetEntityByName("Maxwell");
	}

	void OnTick()
	{
		transform->SetPosition(vec3(player->GetTransform()->GetPosition()) + offset);
		/*if (input->GetKey(Keys::W))
		{
			transform->AddPosition(vec3(0.0f, 0.2f, 0.0f));
		}
		if (input->GetKey(Keys::S))
		{
			transform->AddPosition(vec3(0.0f, -0.2f, 0.0f));
		}
		if (input->GetKey(Keys::A))
		{
			transform->AddPosition(vec3(-0.2f, 0.0f, 0.0f));
		}
		if (input->GetKey(Keys::D))
		{
			transform->AddPosition(vec3(0.2f, 0.0f, 0.0f));
		}*/
	}
};