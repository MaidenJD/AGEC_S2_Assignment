#pragma once

#include "HeadersGL.h"

char* GetFileContents(const char* file)
{
	SDL_RWops *readWriter = SDL_RWFromFile(file, "rb");

	if (readWriter == nullptr)
		return nullptr;

	Sint64 fileSize = SDL_RWsize(readWriter);
	char* source = (char*)malloc(fileSize + 1);

	Sint64 numReadChars = 0;
	Sint64 remainingChars = 1;

	char* buffer = source;

	while (numReadChars < fileSize && remainingChars > 0)
	{
		remainingChars = SDL_RWread(readWriter, buffer, 1, (fileSize - numReadChars));
		numReadChars += remainingChars;
		buffer += remainingChars;
	}

	SDL_RWclose(readWriter);

	if (numReadChars != fileSize)
	{
		free(source);
		return NULL;
	}

	source[numReadChars] = '\0';
	return source;
}