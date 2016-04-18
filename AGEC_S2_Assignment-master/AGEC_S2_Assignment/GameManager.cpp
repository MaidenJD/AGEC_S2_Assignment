#include "GameManager.h"

GameManager* GM = GameManager::GetInstance();

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	VM->Destroy();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

/* -----  INITS  ----- */

bool GameManager::InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error: SDL_Init: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetSwapInterval(1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	window = SDL_CreateWindow("AGEC_S2_Assignment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_W, SCR_H, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cerr << "Error: SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cerr << "Error: SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

bool GameManager::InitGlew()
{
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		std::cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << std::endl;
		return false;
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	return true;
}

bool GameManager::Init()
{
	if (!InitSDL())
		return false;

	if (!InitGlew())
		return false;

	if (!VM->Init())
		return false;

	return true;
}

/* ----- MAIN LOOP ----- */

void GameManager::Run()
{
	Uint32 prevTicks = 0;
	Uint32 newTicks = 0;

	while (VM->Update())
	{
		VM->Render(window);

		newTicks = SDL_GetTicks();
		VM->deltaTime = (newTicks - prevTicks) / 1000.f;
		VM->totalTime = newTicks / 1000.0f;
		prevTicks = newTicks;
	}
}