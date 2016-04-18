#pragma once

#include "HeadersGL.h"

class GameObject;

class Component
{
public:
	Component();
	~Component();

	bool virtual Init();
	void virtual Destroy();

	bool virtual Update();
	void virtual Render();

	GameObject* gameObject;
};

