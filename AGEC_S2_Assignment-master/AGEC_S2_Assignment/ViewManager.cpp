#include "ViewManager.h"

#include "Views.h"

ViewManager* VM = ViewManager::GetInstance();

ViewManager::ViewManager()
{
	IM->AddAction("ESCAPE", SDLK_ESCAPE);
}

ViewManager::~ViewManager()
{
	currentView->Destroy();
	IM->Destroy();
}

bool ViewManager::Init()
{
	return ChangeView<TestView>();
}

bool ViewManager::Update()
{
	system("CLS");

	IM->Update();

	if (IM->ActionPressed("ESCAPE") || IM->GetEvent(SDL_QUIT))
		return false;

	return currentView->Update();
}

void ViewManager::Render(SDL_Window* window)
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	currentView->Render();

	SDL_GL_SwapWindow(window);
}

template<class newView>
bool ViewManager::ChangeView()
{
	if (currentView != nullptr)
		currentView->Destroy();

	currentView = new newView();
	return currentView->Init();
}