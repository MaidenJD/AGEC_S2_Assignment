#include "GameObject.h"
#include "HeadersGL.h"
#include "GameManager.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

bool GameObject::Init()
{
	transform = AddComponent<Transform>();

	if (AddComponent<MeshComponent>() == nullptr)
		return false;

	return true;
}

void GameObject::Destroy()
{
	for each (Component* c in components)
	{
		c->Destroy();
	}

	components.clear();
}

bool GameObject::Update()
{
	return true;
}

bool GameObject::UpdateAll()
{
	for each (GameObject* g in children)
	{
		if (!g->UpdateAll())
			return false;
	}

	for each (Component* c in components)
	{
		if (!c->Update())
			return false;
	}

	return Update();
}

void GameObject::Render()
{
	for each (Component* c in components)
	{
		c->Render();
	}

	for each (GameObject* g in children)
	{
		g->Render();
	}
}