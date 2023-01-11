#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()

using namespace gepEngine;

struct EnemyScript : Component
{
	std::shared_ptr<Entity> player;
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, 0.3f, -3.0f));
		transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
		player = getCore->GetEntityByName("Maxwell");
	}

	void OnTick()
	{
		if (input->GetKey(Keys::X))
		{
			
		}
	}
};