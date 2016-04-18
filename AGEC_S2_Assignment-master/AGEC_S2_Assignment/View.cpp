#include "View.h"
#include "GameManager.h"
#include "GameObjects.h"

View::View()
{
}

View::~View()
{
}

bool View::Init()
{
	for each (GameObject* g in gameObjects)
		g->Init();

	return true;
}

void View::Destroy()
{
	for each (GameObject* g in gameObjects)
		g->Destroy();

	gameObjects.clear();
}

bool View::Update()
{
	for each (GameObject* g in gameObjects)
	{
		if (!g->UpdateAll())
			return false;
	}

	return true;
}

void View::Render()
{
	for each (GameObject* g in gameObjects)
	{
		g->Render();
	}
}