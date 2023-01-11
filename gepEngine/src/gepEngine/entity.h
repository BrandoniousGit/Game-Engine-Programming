#include <vector>
#include <memory>
#include <list>
#include <string>
#include "GlmWrap.h"

namespace gepEngine
{
	struct Component;
	struct Core;
	struct Transform;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->m_self = rtn;
			rtn->m_entity = m_self;
			m_components.push_back(rtn);

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			for (std::list<std::shared_ptr<Component>>::iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*it);

				if (rtn)
				{
					return rtn;
				}
			}

			std::cout << "No component found while getting component" << "\n";
			throw std::runtime_error("Specified component not found");
		}

		std::shared_ptr<Transform> GetTransform();
		std::shared_ptr<Core> GetCore();
		std::string GetName();

	private:
		friend struct Core;

		std::list<std::shared_ptr<Component> > m_components;

		void Initialize();
		void Tick();
		void Display();

		std::string m_name;
		std::weak_ptr<Transform> m_transform;
		std::weak_ptr<Entity> m_self;
		std::weak_ptr<Core> m_core;
	};
}