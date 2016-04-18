#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	bool Init();

	bool Update();

	void Translate(glm::vec2 translation);

	glm::vec4 position;
	glm::mat4 matrix;
};
