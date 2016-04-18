#include "GameManager.h"

int main(int argc, char *args[])
{
	if (GM->Init())
		GM->Run();

	GM->Destroy();

	return 0;
}