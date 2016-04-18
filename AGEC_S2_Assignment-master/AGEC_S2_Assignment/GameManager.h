#pragma once
#include "Singleton.h"
#include "HeadersGL.h"
#include "ViewManager.h"

class GameManager : public Singleton<GameManager>
{
public:
	~GameManager();
	GameManager();

	bool Init();
	void Run();

private:
	bool InitSDL();
	bool InitGlew();

	SDL_GLContext context;
	SDL_Window* window;
};

extern GameManager* GM;
