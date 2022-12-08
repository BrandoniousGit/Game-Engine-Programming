#include "Input.h"

namespace gepEngine
{
	std::list<SDL_Keycode> Input::keys = {};
	std::list<SDL_Keycode> Input::keyDown = {};
	std::list<SDL_Keycode> Input::keyUp = {};

	bool Input::GetKeyDown(SDL_Keycode code)
	{
		for (auto it = Input::keyDown.begin(); it != Input::keyDown.end(); it++)
		{
			if ((*it) == code)
			{
				return true;
			}
		}
		return false;
	}

	bool Input::GetKeyUp(SDL_Keycode code)
	{
		for (auto it = Input::keyUp.begin(); it != Input::keyUp.end(); it++)
		{
			if ((*it) == code)
			{
				return true;
			}
		}
		return false;
	}

	bool Input::GetKey(SDL_Keycode code)
	{
		for (auto it = Input::keys.begin(); it != Input::keys.end(); it++)
		{
			if ((*it) == code)
			{
				return true;
			}
		}
		return false;
	}
}