#include "TestView.h"
#include "GameObjects.h"

TestView::TestView()
{
}

TestView::~TestView()
{
}

bool TestView::Init()
{
	gameObjects.push_back(new TestGO2);
	gameObjects.push_back(new TestGO);

	return View::Init();
}