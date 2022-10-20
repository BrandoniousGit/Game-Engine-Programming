#define SDL_MAIN_HANDLED
#include <memory>
#include <list>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <rend/rend.h>

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
		SDL_Window* m_window;
		SDL_GLContext m_context;
		std::weak_ptr<Core> m_self;
		std::list<std::shared_ptr<Entity> > m_entities; //List of entities;
	};
}