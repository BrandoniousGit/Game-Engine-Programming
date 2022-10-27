#ifndef GEPENGINE_COMPONENT_H
#define GEPENGINE_COMPONENT_H

namespace gepEngine
{
	struct Entity;

	struct Component
	{
	private:
		friend struct Entity;

		virtual void OnTick();
		virtual void OnDisplay();

		virtual void OnInitialize();

		void Tick();
		void Display();
		void Initialize();
	};
}

#endif