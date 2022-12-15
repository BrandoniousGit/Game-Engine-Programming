#ifndef GEPENGINE_SHADER_H
#define GEPENGINE_SHADER_H

#include "Resource.h"
#include <rend/rend.h>
#include <memory>
#include <string>
#include <vector>

namespace gepEngine
{
	struct Shader : Resource
	{
		void OnLoad();

	private:
		std::shared_ptr<rend::Shader> m_shader;
	};
}
#endif