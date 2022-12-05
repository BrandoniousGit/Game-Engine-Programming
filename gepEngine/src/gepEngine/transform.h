#include "component.h"
#include <rend/rend.h>
#include "glmWrap.h"

namespace gepEngine
{
	/**
 * Component providing position information of the Entity.
 */
	struct Transform : Component
	{
	public:
		/**
		* Generate the model matrix based on the position, rotation and
		* scale.
		*
		* \return The generated model matrix
		*/
		rend::mat4 GetModel();
		/**
		* Set the position.
		*
		* \param _position The new position
		*/
		//Setter
		void SetPosition(const vec3& _position) { m_position = _position; }
		void SetRotation(const vec3& _rotation) { m_rotation = _rotation; }
		void SetScale(const vec3& _scale) { m_scale = _scale; }

		void AddPosition(const vec3& _position) { m_position += _position; }
		void AddRotation(const vec3& _rotation) { m_rotation += _rotation; }

		//Getters
		const vec3 GetPosition() { return m_position; }
		const vec3 GetRotation() { return m_rotation; }
		const vec3 GetScale() { return m_scale; }

	private:
		vec3 m_position = vec3(0.0f); ///< X, Y, Z location of Entity
		vec3 m_rotation = vec3(0.0f); ///< Rotation of Entity in euler angles
		vec3 m_scale = vec3(1.0f); ///< Scale of Entity
	};
}