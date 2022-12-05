#ifndef GEPENGINE_BOXCOLLIDER_H
#define GEPENGINE_BOXCOLLIDER_H

#include <iostream>
#include "component.h"
#include "glmWrap.h"

namespace gepEngine
{
	struct BoxCollider : Component
	{
		BoxCollider();

		bool OnCollision(const BoxCollider& _other);

	private:
		vec3 m_scale;
		vec3 m_offset;
	};
}
#endif