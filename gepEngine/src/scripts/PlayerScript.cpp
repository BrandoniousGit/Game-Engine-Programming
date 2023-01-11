#include <gepEngine/gepEngine.h>
#include <iostream>
#include <scripts/Scripts.h>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()

using namespace gepEngine;

struct PlayerScript : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, 0.0f, 0.0f));
		transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	}

	void OnTick()
	{
		if (input->GetKey(Keys::W))
		{
			transform->AddPosition(vec3(0.0f, 0.0f, -0.2f));
		}
		if (input->GetKey(Keys::S))
		{
			transform->AddPosition(vec3(0.0f, 0.0f, 0.2f));
		}
		if (input->GetKey(Keys::A))
		{
			transform->AddPosition(vec3(-0.2f, 0.0f, 0.0f));
		}
		if (input->GetKey(Keys::D))
		{
			transform->AddPosition(vec3(0.2f, 0.0f, 0.0f));
		}
	}
};