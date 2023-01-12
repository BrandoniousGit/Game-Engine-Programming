#include <gepEngine/gepEngine.h>
#include <iostream>

#define entity GetEntity()
#define transform GetEntity()->GetTransform()
#define input GetEntity()->GetCore()->GetInput()
#define getCore GetEntity()->GetCore()
#define getComponent GetEntity()->GetComponent

using namespace gepEngine;

struct PlayerScript : Component
{
	int startTime;

	bool movingUp, rotating, dancing;

	void OnInitialize();

	void OnTick();
};
