#ifndef GEPENGINE_TIME_H
#define GEPENGINE_TIME_H

#include <iostream>
#include <chrono>
#include "SDL2/SDL.h"

namespace gepEngine
{
	struct Time
	{
		/**
		* @brief Constructor
		*/
		Time();

		/**
		* @brief A getter for delta time
		* @return float
		*/
		static double DeltaTime();

		/**
		 * @brief Gets the current time in seconds
		 * @return The current time in seconds
		*/
		static double GetTimeSeconds() { return SDL_GetTicks() / 1000; }

		/**
		 * @brief Gets the current time in milliseconds
		 * @return The current time in milliseconds
		*/
		static double GetTimeMilliSeconds() { return SDL_GetTicks(); }

	private:
		friend struct Core;

		void Update();

		static double m_deltaTime;
		double m_lastTime;
		double m_currentTime;
		double m_frameRate;
		double m_diff;
	};
}
#endif