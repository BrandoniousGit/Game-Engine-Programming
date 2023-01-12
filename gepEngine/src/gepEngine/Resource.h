#ifndef GEPENGINE_RESOURCE_H
#define GEPENGINE_RESOURCE_H

#include <memory>
#include <string>
#include <vector>

namespace gepEngine
{
	struct Cache;

	struct Resource
	{
		virtual void OnLoad() = 0;

		/**
		 * @brief Gets the path to the resource
		 * @return 
		*/
		std::string GetPath() const;

	private:
		friend struct Cache;
		std::string m_path;

		void Load();
	};
}
#endif