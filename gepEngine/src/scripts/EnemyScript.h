#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()

using namespace gepEngine;

struct EnemyScript : Component
{
	void OnInitialize();

	void OnTick();
};