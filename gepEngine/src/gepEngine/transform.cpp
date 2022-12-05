#include "transform.h"

namespace gepEngine
{
	rend::mat4 Transform::GetModel()
	{
		mat4 translateMat = mat4(1.0f);
		mat4 rotateMat = mat4(1.0f);
		mat4 scaleMat = mat4(1.0f);

		translateMat = translate(translateMat, m_position);

		//funny rotation stuff
		rotateMat = rotate(rotateMat, radians(m_rotation.x), vec3(1.0f, 0.0f, 0.0f));
		rotateMat = rotate(rotateMat, radians(m_rotation.y), vec3(0.0f, 1.0f, 0.0f));
		rotateMat = rotate(rotateMat, radians(m_rotation.z), vec3(0.0f, 0.0f, 1.0f));

		scaleMat = scale(scaleMat, m_scale);

		return translateMat * rotateMat * scaleMat;
	}
}