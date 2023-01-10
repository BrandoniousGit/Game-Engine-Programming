#include "Time.h"

namespace gepEngine
{
    double Time::m_deltaTime = 0;

    Time::Time()
    {
        m_currentTime = static_cast<double>(SDL_GetTicks());
        m_lastTime = 0.0f;
        m_deltaTime = 0.0f;
        m_frameRate = 1.0f / 60.0f; // Limit the game to 60fps
    }

    double Time::DeltaTime()
    {
        return m_deltaTime;
    }

    void Time::Update()
    {
        // Compute time elapsed since last frame
        m_currentTime = static_cast<double>(SDL_GetTicks());

        // DeltaTime Compution
        m_diff = m_currentTime - m_lastTime;

        m_deltaTime = m_diff / 1000.0f; // covert to seconds

        // if DeltaTime is less than the framerate, add delay to the game
        if (m_deltaTime < m_frameRate)
        {
            SDL_Delay((Uint32)(m_frameRate - m_deltaTime) * 1000.0f); // convert back to milliseconds
        }

        m_lastTime = static_cast<double>(SDL_GetTicks());
    }
}