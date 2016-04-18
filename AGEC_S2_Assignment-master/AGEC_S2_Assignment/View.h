#pragma once
#include <vector>

class GameObject;

class View
{
public:
	View();
	~View();

	bool virtual Init();
	void Destroy();

	bool Update();
	void Render();

protected:
	std::vector<GameObject*> gameObjects;
};

