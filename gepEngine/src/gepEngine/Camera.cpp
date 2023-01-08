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
		std::shared_ptr<Transform> trans = GetEntity()->GetTransform();

		mat4 rotationMat = mat4(1.0f);
		mat4 translationMat = mat4(1.0f);;

		translationMat = glm::translate(translationMat, -trans->GetPosition());
		rotationMat = rotate(rotationMat, radians(-trans->GetRotation().y), vec3(0.0f, 1.0f, 0.0f)); // favouring y
		rotationMat = rotate(rotationMat, radians(-trans->GetRotation().x), vec3(1.0f, 0.0f, 0.0f));
		rotationMat = rotate(rotationMat, radians(-trans->GetRotation().z), vec3(0.0f, 0.0f, 1.0f));

		return translationMat * rotationMat;
	}
}