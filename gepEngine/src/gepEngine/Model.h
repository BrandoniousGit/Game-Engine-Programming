#ifndef GEPENGINE_MODEL_H
#define GEPENGINE_MODEL_H

#include "Resource.h"
#include <iostream>
#include <rend/rend.h>
#include <vector>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>

namespace gepEngine
{
	struct MeshRenderer;
	struct Model : Resource
	{
		/**
		 * @brief Loads the model into the cache
		 * @param _path 
		*/
		void load_model(const std::string _path);

		void OnLoad();

	private:
		friend MeshRenderer;
		std::shared_ptr<rend::Model> m_model;
	};
}
#endif