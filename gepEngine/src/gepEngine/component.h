#ifndef GEPENGINE_COMPONENT_H
#define GEPENGINE_COMPONENT_H
#include <memory>

namespace gepEngine
{
	struct Entity;

	struct Component
	{
	public:
		/**
		 * @brief Gets the current entity
		 * @return shared_ptr<Entity>
		*/
		std::shared_ptr<Entity> GetEntity() const;

	private:
		friend struct Entity;

		/**
		 * @brief Runs each frame
		*/
		virtual void OnTick();
		virtual void OnDisplay();
		/**
		 * @brief Runs once on initialize
		*/
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