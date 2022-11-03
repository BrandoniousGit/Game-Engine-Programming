#include <vector>
#include <memory>
#include "glmWrap.h"

namespace gepEngine
{
	struct Component;
	struct Core;
	struct Transform;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_self = rtn;
			rtn->m_entity = m_self;
			m_components.push_back(rtn);

			return rtn;
		}

		std::shared_ptr<Transform> getTransform();

	private:
		friend struct Core;

		std::vector<std::shared_ptr<Component> > m_components;

		void Initialize();
		void Tick();
		void Display();

		std::weak_ptr<Transform> m_transform;
		std::weak_ptr<Entity> m_self;
		std::weak_ptr<Core> m_core;
	};
}