#pragma once
#include "Component.h"
class AlphaFadeComponent :
	public Component
{
public:
	AlphaFadeComponent();
	~AlphaFadeComponent();

	bool Init();
	bool InitFade();

	bool Update();

private:
	GLuint fadeVarLoc;
	GLuint relProg;
};

