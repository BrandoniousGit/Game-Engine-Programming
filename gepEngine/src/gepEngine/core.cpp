#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Cache.h"
#include "Input.h"

#include <stdexcept>

namespace gepEngine
{
	std::shared_ptr<Core> Core::Initialize() //Engine core
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;
		rtn->m_running = false; //Initialising running bool because otherwise it's a garbage value

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initialise SDL");
		}

		if (!(rtn->m_window = SDL_CreateWindow("SDL2 Platform",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			720, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create window");
		}
			
		if (!(rtn->m_context = SDL_GL_CreateContext(rtn->m_window)))
		{
			SDL_DestroyWindow(rtn->m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}

		/*************************************************************************
		* Initialization
		*************************************************************************/
		rtn->m_audioDevice = alcOpenDevice(NULL);

		if (!rtn->m_audioDevice)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		rtn->m_audioContext = alcCreateContext(rtn->m_audioDevice, NULL);

		if (!rtn->m_audioContext)
		{
			alcCloseDevice(rtn->m_audioDevice);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(rtn->m_audioContext))
		{
			alcDestroyContext(rtn->m_audioContext);
			alcCloseDevice(rtn->m_audioDevice);
			throw std::runtime_error("Failed to make context current");
		}

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

		rtn->m_cache = std::make_shared<Cache>();

		return rtn;
	}

	std::shared_ptr<Entity> Core::AddEntity() //Function to add entity to scene
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_transform = rtn->AddComponent<Transform>();

		rtn->m_self = rtn;
		rtn->m_core = m_self;
		m_entities.push_back(rtn);

		return rtn;
	}

	void Core::Start() //Runs once on engine start
	{
		m_running = true;

		for (auto it = m_entities.begin(); it != m_entities.end(); it++)
		{
			(*it)->Initialize();
		}

		//Loop

		while (m_running)
		{
			SDL_Event event = { 0 };
			while (SDL_PollEvent(&event))
			{
				int button;
				switch (event.type)
				{
				case SDL_QUIT:
					m_running = false;
					break;

				case SDL_KEYDOWN:
					if (!m_input->GetKey(event.key.keysym.sym))
					{
						m_input->keyDown.push_back(event.key.keysym.sym);
						m_input->keys.push_back(event.key.keysym.sym);
					}
					break;

				case SDL_KEYUP:
					if (m_input->GetKey(event.key.keysym.sym))
					{
						m_input->keys.remove(event.key.keysym.sym);
						m_input->keyUp.push_back(event.key.keysym.sym);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:

					button = (int)event.button.button;
					m_input->buttons.push_back(button);
					m_input->buttonDown.push_back(button);

					break;
				case SDL_MOUSEBUTTONUP:

					button = (int)event.button.button;
					m_input->buttons.remove(button);
					m_input->buttonUp.push_back(button);

					break;
				}
			}
			
			for (auto it = m_entities.begin(); it != m_entities.end(); it++)
			{
				(*it)->Tick();
			}

			rend::Renderer r(720, 720);
			r.clear();

			for (auto it = m_entities.begin(); it != m_entities.end(); it++)
			{
				(*it)->Display();
			}
			SDL_GL_SwapWindow(m_window);;
		}
	}

	void Core::Stop() //Runs once on engine quit
	{
		m_running = false;
	}

	std::shared_ptr<Cache> Core::GetCache()
	{
		return m_cache;
	}

	std::shared_ptr<Input> Core::GetInput()
	{
		return m_input;
	}
}