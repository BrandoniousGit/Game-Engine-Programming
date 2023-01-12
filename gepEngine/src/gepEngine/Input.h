#ifndef GEPENGINE_INPUT_H
#define GEPENGINE_INPUT_H

#include <SDL2/SDL.h>
#include <iostream>
#include <list>
#include "glmWrap.h"

namespace gepEngine
{
	struct Input
	{
		/**
		 * @brief Returns true while holding a given key down
		 * @param code 
		 * @return bool
		*/
		bool GetKey(SDL_Keycode code);
		/**
		 * @brief Returns true when a given key is pressed
		 * @param code 
		 * @return bool
		*/
		bool GetKeyDown(SDL_Keycode code);
		/**
		 * @brief Returns true when a given key is released
		 * @param code 
		 * @return bool
		*/
		bool GetKeyUp(SDL_Keycode code);
		/**
		 * @brief Returns true when a given mouse button is held
		 * @param button 
		 * @return bool
		*/
		bool GetButton(int button);
		/**
		 * @brief Returns true when a given mouse button is pressed
		 * @param button 
		 * @return bool
		*/
		bool GetButtonDown(int button);
		/**
		 * @brief Returns true when a given mouse button is released
		 * @param button
		 * @return bool
		*/
		bool GetButtonUp(int button);
		/**
		 * @brief Gets the current mouse position
		 * @return vec3
		*/
		vec3 GetMousePos() { return vec3(mousePos.x, mousePos.y, 0.0f); }

	private:
		friend struct Core;

		static std::list<SDL_Keycode> keys;
		static std::list<SDL_Keycode> keyDown;
		static std::list<SDL_Keycode> keyUp;
		static std::list<int> buttons;
		static std::list<int> buttonDown;
		static std::list<int> buttonUp;
		static vec3 mousePos;
	};

	struct Keys
	{
		static const int UP = SDLK_UP;
		static const int DOWN = SDLK_DOWN;
		static const int LEFT = SDLK_LEFT;
		static const int RIGHT = SDLK_RIGHT;
		static const int A = SDLK_a;
		static const int B = SDLK_b;
		static const int C = SDLK_c;
		static const int D = SDLK_d;
		static const int E = SDLK_e;
		static const int F = SDLK_f;
		static const int G = SDLK_g;
		static const int H = SDLK_h;
		static const int I = SDLK_i;
		static const int J = SDLK_j;
		static const int K = SDLK_k;
		static const int L = SDLK_l;
		static const int M = SDLK_m;
		static const int N = SDLK_n;
		static const int O = SDLK_o;
		static const int P = SDLK_p;
		static const int Q = SDLK_q;
		static const int R = SDLK_r;
		static const int S = SDLK_s;
		static const int T = SDLK_t;
		static const int U = SDLK_u;
		static const int V = SDLK_v;
		static const int W = SDLK_w;
		static const int X = SDLK_x;
		static const int Y = SDLK_y;
		static const int Z = SDLK_z;
		static const int key_0 = SDLK_0;
		static const int key_1 = SDLK_1;
		static const int key_2 = SDLK_2;
		static const int key_3 = SDLK_3;
		static const int key_4 = SDLK_4;
		static const int key_5 = SDLK_5;
		static const int key_6 = SDLK_6;
		static const int key_7 = SDLK_7;
		static const int key_8 = SDLK_8;
		static const int key_9 = SDLK_9;
		static const int FN_1 = SDLK_F1;
		static const int FN_2 = SDLK_F2;
		static const int FN_3 = SDLK_F3;
		static const int FN_4 = SDLK_F4;
		static const int FN_5 = SDLK_F5;
		static const int FN_6 = SDLK_F6;
		static const int FN_7 = SDLK_F7;
		static const int FN_8 = SDLK_F8;
		static const int FN_9 = SDLK_F9;
		static const int FN_10 = SDLK_F10;
		static const int FN_11 = SDLK_F11;
		static const int FN_12 = SDLK_F12;
		static const int SPACE = SDLK_SPACE;
		static const int BACKSPACE = SDLK_BACKSPACE;
		static const int RETURN = SDLK_RETURN;
		static const int ENTER = SDLK_KP_ENTER;
		static const int LSHIFT = SDLK_LSHIFT;
		static const int RSHIFT = SDLK_RSHIFT;
		static const int LCTRL = SDLK_LCTRL;
		static const int RCTRL = SDLK_RCTRL;
		static const int LALT = SDLK_LALT;
		static const int RALT = SDLK_RALT;
		static const int TAB = SDLK_TAB;
		static const int CAPSLOCK = SDLK_CAPSLOCK;
		static const int INSERT = SDLK_INSERT;
		static const int DELETE = SDLK_DELETE;
		static const int HOME = SDLK_HOME;
		static const int END = SDLK_END;
		static const int PGUP = SDLK_PAGEUP;
		static const int PGDN = SDLK_PAGEDOWN;
		static const int PRINTSCREEN = SDLK_PRINTSCREEN;
		static const int SCROLLLOCK = SDLK_SCROLLLOCK;
		static const int PAUSE = SDLK_PAUSE;
		static const int NUM_0 = SDLK_KP_0;
		static const int NUM_1 = SDLK_KP_1;
		static const int NUM_2 = SDLK_KP_2;
		static const int NUM_3 = SDLK_KP_3;
		static const int NUM_4 = SDLK_KP_4;
		static const int NUM_5 = SDLK_KP_5;
		static const int NUM_6 = SDLK_KP_6;
		static const int NUM_7 = SDLK_KP_7;
		static const int NUM_8 = SDLK_KP_8;
		static const int NUM_9 = SDLK_KP_9;
		static const int NUM_DOT = SDLK_KP_PERIOD;
		static const int NUM_ADD = SDLK_KP_PLUS;
		static const int NUM_MINUS = SDLK_KP_MINUS;
		static const int NUM_MULTIPLY = SDLK_KP_MULTIPLY;
		static const int NUM_DIVIDE = SDLK_KP_DIVIDE;
		static const int MINUS = SDLK_MINUS;
		static const int PLUS = SDLK_PLUS;
		static const int SEMICOLON = SDLK_SEMICOLON;
		static const int AT = SDLK_AT;
		static const int HASH = SDLK_HASH;
		static const int SLASH = SDLK_SLASH;
		static const int BACKSLASH = SDLK_BACKSLASH;
		static const int PERIOD = SDLK_PERIOD;
		static const int COMMA = SDLK_COMMA;
		static const int LSQUAREBRACKET = SDLK_LEFTBRACKET;
		static const int RSQUAREBRACKET = SDLK_RIGHTBRACKET;
	};
}

#endif