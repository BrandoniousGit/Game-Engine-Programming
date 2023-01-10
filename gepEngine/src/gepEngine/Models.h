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
	struct Models : Resource
	{
		rend::Model* GetRendModel() { return m_model; }

		void load_model(const std::string _path);

		void OnLoad();

	private:
		rend::Model* m_model;
	};
}
#endif