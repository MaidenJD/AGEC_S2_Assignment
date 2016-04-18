#include "AlphaFadeComponent.h"
#include "GameObject.h"
#include "GameManager.h"

AlphaFadeComponent::AlphaFadeComponent()
{
}


AlphaFadeComponent::~AlphaFadeComponent()
{
}


bool AlphaFadeComponent::Init()
{
	return true;
}

bool AlphaFadeComponent::InitFade()
{
	relProg = gameObject->GetComponent<MeshComponent>()->program;

	fadeVarLoc = glGetUniformLocation(relProg, "fade");
	return true;
}

bool AlphaFadeComponent::Update()
{
	float fade = sinf(VM->totalTime * (2 * 3.14) / 5) / 2 + 0.5;
	glUseProgram(relProg);
	glUniform1f(fadeVarLoc, fade);

	return true;
}
