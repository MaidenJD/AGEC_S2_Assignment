#pragma once
#include "GameObject.h"
class TestGO2 : public GameObject
{
public:
	TestGO2();
	~TestGO2();

	virtual bool Init();
	virtual void Destroy();

	virtual bool Update();

private:

	float speed;
};
