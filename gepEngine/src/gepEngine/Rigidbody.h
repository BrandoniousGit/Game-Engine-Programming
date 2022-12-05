#ifndef GEPENGINE_RIGIDBODY_H
#define GEPENGINE_RIGIDBODY_H

#include <iostream>
#include "component.h"

namespace gepEngine
{
	struct Rigidbody : Component
	{
		void OnTick();
	};
}
#endif