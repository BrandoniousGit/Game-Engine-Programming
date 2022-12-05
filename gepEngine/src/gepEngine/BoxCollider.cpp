#include "BoxCollider.h"
#include "transform.h"
#include "entity.h"

namespace gepEngine
{
	BoxCollider::BoxCollider()
	{
		m_scale = vec3(1.0f);
		m_offset = vec3(0.0f);
	}

	bool BoxCollider::OnCollision(const BoxCollider& _other)
	{
		vec3 bc1 = GetEntity()->GetTransform()->GetPosition();
		vec3 bc2 = _other.GetEntity()->GetTransform()->GetPosition();

		vec3 bc1Size = m_scale / 2.0f;
		vec3 bc2Size = _other.m_scale / 2.0f;


		//X Collision checking

		if (bc1.x > bc2.x)
		{
			if (bc1.x - bc1Size.x < bc2.x + bc2Size.x)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		if (bc2.x > bc1.x)
		{
			if (bc2.x - bc2Size.x < bc1.x + bc1Size.x)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		//Y Collision checking

		if (bc1.y > bc2.y)
		{
			if (bc1.y - bc1Size.y < bc2.y + bc2Size.y)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		if (bc2.y > bc1.y)
		{
			if (bc2.y - bc2Size.y < bc1.y + bc1Size.y)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		//Z Collision checking

		if (bc1.z > bc2.z)
		{
			if (bc1.z - bc1Size.z < bc2.z + bc2Size.z)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		if (bc2.z > bc1.z)
		{
			if (bc2.z - bc2Size.z < bc1.z + bc1Size.z)
			{
				std::cout << "Colliding";
				return true;
			}
		}

		return false;
	}
}