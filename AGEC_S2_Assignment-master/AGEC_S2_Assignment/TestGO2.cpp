#include "TestGO2.h"
#include "GameManager.h"

TestGO2::TestGO2()
{
}

TestGO2::~TestGO2()
{
}

bool TestGO2::Init()
{
	if (!GameObject::Init())
		return false;

	IM->AddAxis("moveUp2", SDLK_UP, SDLK_DOWN);
	IM->AddAxis("moveRight2", SDLK_RIGHT, SDLK_LEFT);

	speed = 5;

	return true;
}

void TestGO2::Destroy()
{
	GameObject::Destroy();
}

bool TestGO2::Update()
{
	glm::vec2 translation;

	translation.x = IM->GetAxis("moveRight2") * speed * VM->deltaTime;
	translation.y = IM->GetAxis("moveUp2") * speed * VM->deltaTime;

	transform->Translate(translation);

	return true;
}