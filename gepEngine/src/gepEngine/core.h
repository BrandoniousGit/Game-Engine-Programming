#define SDL_MAIN_HANDLED
#include <memory>
#include <list>
#include <vector>
#include <string>
                                                              
#include <AL/al.h>
#include <AL/alc.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <rend/rend.h>

namespace gepEngine
{
	struct Entity;
	struct Cache;
	struct Input;

	struct Core
	{
		/**
		 * @brief Initializes the core
		 * @return shared_ptr<Core>
		*/
		static std::shared_ptr<Core> Initialize();
		/**
		 * @brief Adds an entity to the scene
		 * @param _name 
		 * @return shared_ptr<Entity>
		*/
		std::shared_ptr<Entity> AddEntity(std::string _name);

		/**
		 * @brief Starts the core
		*/
		void Start();
		/**
		 * @brief Stops the core
		*/
		void Stop();

		template <typename T>
		/**
		 * @brief Finds all components of a given type
		 * @tparam T 
		 * @param _out 
		*/
		void Find(std::vector<std::shared_ptr<T>>& _out)
		{
			// Go through each Entity in Core.
			for (std::list<std::shared_ptr<Entity>>::iterator it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				std::shared_ptr<Entity> e = *it;
				// Go through each Component in Entity.
				for (std::list<std::shared_ptr<Component>>::iterator itt = e->m_components.begin(); itt != e->m_components.end(); ++itt)
				{
					std::shared_ptr<Component> c = *itt;
					// Try to dynamic cast the Component to a T.
					std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
					// If succeeds then add it to the output array.
					if (t)
					{
						_out.push_back(t);
					}
				}
			}
		}

		/**
		 * @brief Returns the Cache
		 * @return shared_ptr<Cache>
		*/
		std::shared_ptr<Cache> GetCache();
		/**
		 * @brief Returns the Input
		 * @return shared_ptr<Cache>
		*/
	    std::shared_ptr<Input> GetInput();
		/**
		 * @brief Gets an entity given the name
		 * @param _name 
		 * @return shared_ptr<Entity>
		*/
		std::shared_ptr<Entity> GetEntityByName(std::string _name);

	private:
		ALCcontext *m_audioContext;
		ALCdevice *m_audioDevice;

		std::shared_ptr<Cache> m_cache;
		std::shared_ptr<Input> m_input;

		bool m_running; //Flag to keep engine running
		SDL_Window* m_window;
		SDL_GLContext m_context; 
		std::weak_ptr<Core> m_self;
		std::list<std::shared_ptr<Entity> > m_entities; //List of entities;
	};
}