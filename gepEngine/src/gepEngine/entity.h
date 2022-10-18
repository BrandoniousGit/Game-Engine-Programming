#include <vector>
#include <memory>

namespace gepEngine
{
	struct Component;
	struct Core;

	struct Entity
	{
		/*template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr
		}*/

	private:
		friend struct Core;

		//std::vector<std::shared_ptr<Component> > m_components;

		void tick();
		void display();
	};
}