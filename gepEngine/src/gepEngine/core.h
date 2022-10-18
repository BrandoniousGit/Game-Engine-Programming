#include <memory>
#include <list>

namespace gepEngine
{
	struct Entity;
	struct Core
	{
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();

		void start();
		void stop();

	private:
		bool m_running; //Flag to keep engine running
		std::list<std::shared_ptr<Entity> > m_entities; //List of entities;
	};
}