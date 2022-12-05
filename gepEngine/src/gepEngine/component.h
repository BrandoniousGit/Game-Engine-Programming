#ifndef GEPENGINE_COMPONENT_H
#define GEPENGINE_COMPONENT_H
#include <memory>

namespace gepEngine
{
	struct Entity;

	struct Component
	{
	public:
		std::shared_ptr<Entity> GetEntity() const;

	private:
		friend struct Entity;

		virtual void OnTick();
		virtual void OnDisplay();

		virtual void OnInitialize();

		void Tick();
		void Display();
		void Initialize();

	protected:
		std::weak_ptr<Component> m_self;
		std::weak_ptr<Entity> m_entity;
	};
}

#endif