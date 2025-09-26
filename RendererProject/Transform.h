#pragma once

#include "glm/glm.hpp"            // core glsl types
#include "glm/gtx/quaternion.hpp" // quaternion



	class Transform 
	{
	public:

	glm::vec3 LocalPos;
	glm::quat LocalRot;
	glm::vec3 LocalScl;

	Transform();


	// get/set world-space position
	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position);

	// get/set world-space rotation
	glm::quat GetRotation() const;
	void SetRotation(glm::quat rotation);

	// get/set world-space forward
	glm::vec3 GetForward() const;
	void SetForward(glm::vec3 forward);




	glm::mat4 LocalMat() const;
	};

