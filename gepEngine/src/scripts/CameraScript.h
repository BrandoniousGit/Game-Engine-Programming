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
	vec3 playerTransform;
	vec3 offset;

	float ySens, xSens;

	void OnInitialize();

	void OnTick();
};