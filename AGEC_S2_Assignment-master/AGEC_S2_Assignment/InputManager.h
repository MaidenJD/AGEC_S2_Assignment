#pragma once
#include "Singleton.h"

#include "HeadersGL.h"

#include <string>
#include <set>
#include <map>
#include <vector>

enum axisEnd {
	AXIS_POSITIVE_END,
	AXIS_NEGATIVE_END
};

struct axisKeys
{
	std::vector<SDL_Keycode> positiveKeys;
	std::vector<SDL_Keycode> negativeKeys;
};

class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

	void Update();

	bool GetKeyPressed(SDL_Keycode key);
	bool GetKeyReleased(SDL_Keycode key);
	bool GetKeyHeld(SDL_Keycode key);
	bool GetEvent(SDL_EventType eventType);
	int  GetAxis(std::string name);

	void AddAxis(std::string name);
	void AddAxis(std::string name, SDL_Keycode positiveKey, SDL_Keycode negativeKey);
	void BindKeyToAxis(std::string axis, axisEnd endToRebind, SDL_Keycode key);
	void UnbindKeyFromAxis(std::string axis, axisEnd endToRemove);
	void UnbindAllKeysFromAxis(std::string axis);

	void RebindAxis(std::string axis, axisEnd type, SDL_Keycode key);

	void AddAction(std::string name);
	void AddAction(std::string name, SDL_Keycode binding);
	void RebindAction(std::string action, SDL_Keycode newBinding);
	void UnbindAction(std::string action);
	bool ActionPressed(std::string action);
	bool ActionReleased(std::string action);

private:
	std::set<SDL_Keycode> keysDown;
	std::set<SDL_Keycode> keysUp;
	std::set<SDL_Keycode> keysHeld;
	std::map<std::string, SDL_Keycode> actions;
	std::map<std::string, axisKeys> axes;

	std::set<SDL_EventType> events;
};

extern InputManager* IM;
