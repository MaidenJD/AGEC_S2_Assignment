#pragma once
#include "GameObject.h"

class TestGO : public GameObject
{
public:
	TestGO();
	~TestGO();

	virtual bool Init();
	virtual void Destroy();

	virtual bool Update();

private:

	float speed;
};
