#include "RigidBody.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "Core.h"
#include <vector>
#include <memory>

namespace gepEngine
{
	void Rigidbody::OnTick()
	{
		std::vector<std::shared_ptr<BoxCollider>> colliders;

		GetEntity()->GetCore()->Find<BoxCollider>(colliders);

		std::shared_ptr<BoxCollider> collider = GetEntity()->GetComponent<BoxCollider>();

		for (size_t i = 0; i < colliders.size(); i++)
		{
			if (colliders.at(i)->GetEntity() == GetEntity())
			{
				continue;
			}

			if (colliders.at(i)->OnCollision(*collider))
			{
				std::cout << "Colliding!\n";
			}
		}
	}
}