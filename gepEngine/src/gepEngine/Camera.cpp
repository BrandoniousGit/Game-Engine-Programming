#include "Camera.h"
#include "Transform.h"
#include "Entity.h"

namespace gepEngine
{
	std::shared_ptr<Camera> Camera::m_main = nullptr;

	std::shared_ptr<Camera> Camera::GetMainCam()
	{
		return m_main;
	}

	mat4 Camera::GetProjection()
	{
		int width = 720, height = 720;

		return glm::perspective(radians(70.0f), (float)width / (float)height, 0.1f, 100.0f);
	}
	mat4 Camera::GetView()
	{
		return glm::inverse(GetEntity()->GetTransform()->GetModel());
	}
}