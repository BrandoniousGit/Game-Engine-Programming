#ifndef GEPENGINE_COMPONENT_H
#define GEPENGINE_COMPONENT_H

namespace gepEngine
{
	struct Entity;

	struct Component
	{
	private:
		friend struct Enitity;

		virtual void onTick();
		virtual void onDisplay();

		void tick();
		void display();
	};
}

#endif