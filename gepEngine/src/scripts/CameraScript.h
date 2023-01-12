#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()
#define getComponent GetEntity()->GetComponent

using namespace gepEngine;

struct CameraScript : Component
{
	std::shared_ptr<Entity> player;
	vec3 playerTransform;
	vec3 offset;

	float ySens, xSens, moveSpeed;

	void OnInitialize();

	void OnTick();
};