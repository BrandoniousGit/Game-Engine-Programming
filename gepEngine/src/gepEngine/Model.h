#ifndef GEPENGINE_MODEL_H
#define GEPENGINE_MODEL_H

#include "Resource.h"
#include <rend/rend.h>
#include <memory>
#include <string>
#include <vector>

namespace gepEngine
{
	struct Model : Resource
	{
		static void load_model(const std::string& _path);

		void OnLoad();

	private:
		std::shared_ptr<rend::Model> m_model;
	};
}
#endif