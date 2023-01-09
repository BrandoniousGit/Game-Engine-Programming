#include "Input.h"

namespace gepEngine
{
	std::list<SDL_Keycode> Input::keys = {};
	std::list<SDL_Keycode> Input::keyDown = {};
	std::list<SDL_Keycode> Input::keyUp = {};
	std::list<int> Input::buttons = {};
	std::list<int> Input::buttonDown = {};
	std::list<int> Input::buttonUp = {};

	bool Input::GetKeyDown(SDL_Keycode code)
	{
		for (auto it = Input::keyDown.begin(); it != Input::keyDown.end(); it++)
		{
			if ((*it) == code)
			{
				keyDown.remove(*it);
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
				keyUp.remove(*it);
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

	bool Input::GetButtonDown(int button)
	{
		for (auto it = Input::buttonDown.begin(); it != Input::buttonDown.end(); it++)
		{
			if ((*it) == button)
			{
				buttonDown.remove(*it);
				return true;
			}
		}
		return false;
	}

	bool Input::GetButtonUp(int button)
	{
		for (auto it = Input::buttonUp.begin(); it != Input::buttonUp.end(); it++)
		{
			if ((*it) == button)
			{
				buttonUp.remove(*it);
				return true;
			}
		}
		return false;
	}

	bool Input::GetButton(int button)
	{
		for (auto it = Input::buttons.begin(); it != Input::buttons.end(); it++)
		{
			if ((*it) == button)
			{
				return true;
			}
		}
		return false;
	}
}