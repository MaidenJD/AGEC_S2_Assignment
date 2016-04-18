#pragma once
#include "Singleton.h"
#include "HeadersGL.h"
#include "InputManager.h"

class View;

class ViewManager : public Singleton<ViewManager>
{
public:
	ViewManager();
	~ViewManager();

	bool Init();

	bool Update();
	void Render(SDL_Window* window);

	float deltaTime;
	float totalTime;

private:

	View* currentView;

	template<class newView>
	bool ChangeView();
};

extern ViewManager* VM;
