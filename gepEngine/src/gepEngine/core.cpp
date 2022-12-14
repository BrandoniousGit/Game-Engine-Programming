#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Cache.h"
#include "Input.h"
#include "Time.h"

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
		rtn->m_input = std::make_shared<Input>();

		return rtn;
	}

	std::shared_ptr<Entity> Core::AddEntity(std::string _name) //Function to add entity to scene
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_transform = rtn->AddComponent<Transform>();
		rtn->m_name = _name;

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

		float idealTime = 1.0f / 60.0f;

		bool Mousefirst = true;
		m_input->mouseMotion = false;
		SDL_SetRelativeMouseMode(SDL_TRUE);

		//Loop

		while (m_running)
		{
			SDL_Event event = { 0 };

			if (idealTime > Time::DeltaTime())
			{
				SDL_Delay(idealTime - Time::DeltaTime() * 1000.0f);
			}

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
				case SDL_MOUSEMOTION:

					m_input->mouseMotion = true;
					if (!Mousefirst)
					{
						m_input->mousePos.x = event.motion.xrel;
						m_input->mousePos.y = event.motion.yrel;
					}
					else
					{
						Mousefirst = false;
						m_input->mousePos.x = 0;
						m_input->mousePos.y = 0;
					}

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

	std::shared_ptr<Entity> Core::GetEntityByName(std::string _name)
	{
		for (auto const it : Core::m_entities)
		{
			if (it->GetName() == _name)
			{
				return it;
			}
		}
		return NULL;
	}
}