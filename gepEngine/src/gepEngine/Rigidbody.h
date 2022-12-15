#ifndef GEPENGINE_RIGIDBODY_H
#define GEPENGINE_RIGIDBODY_H

#include <iostream>
#include "Component.h"

namespace gepEngine
{
	struct Rigidbody : Component
	{
		void OnTick();
	};
}
#endif