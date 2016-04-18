#include "Transform.h"
#include "GameObject.h"
#include "GameManager.h"

#include <glm\gtc\matrix_transform.hpp>

Transform::Transform()
{
}

Transform::~Transform()
{
}

bool Transform::Init()
{
	position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

void Transform::Translate(glm::vec2 translation)
{
	position.x += translation.x;
	position.y += translation.y;
}

bool Transform::Update()
{
	float angle = 0;

	glm::vec3 forward = glm::vec3(0, 0, 1);

	matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position)) * glm::rotate(glm::mat4(1.0f), glm::radians(angle), forward);

	return true;
}

