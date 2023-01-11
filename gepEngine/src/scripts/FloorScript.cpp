#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()

using namespace gepEngine;

struct FloorScript : Component
{
	void OnInitialize()
	{
		transform->SetPosition(vec3(0.0f, -5.0f, 0.0f));
		transform->SetScale(vec3(1, 1, 1));
	}

	void OnTick()
	{

	}
};