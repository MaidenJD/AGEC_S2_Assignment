#include "TestGO.h"
#include "GameManager.h"

TestGO::TestGO()
{
}

TestGO::~TestGO()
{
}

bool TestGO::Init()
{
	if (!GameObject::Init())
		return false;

	IM->AddAxis("moveUp", SDLK_w, SDLK_s);
	IM->AddAxis("moveRight", SDLK_d, SDLK_a);

	speed = 5;

	return true;
}

void TestGO::Destroy()
{
	GameObject::Destroy();
}

bool TestGO::Update()
{
	glm::vec2 translation;

	translation.x = IM->GetAxis("moveRight") * speed * VM->deltaTime;
	translation.y = IM->GetAxis("moveUp") * speed * VM->deltaTime;

	transform->Translate(translation);

	return true;
}