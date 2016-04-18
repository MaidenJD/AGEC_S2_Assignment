#include "InputManager.h"

InputManager* IM = InputManager::GetInstance();

InputManager::InputManager()
{
	keysDown.clear();
	keysUp.clear();

	keysHeld.clear();

	events.clear();
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	events.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (std::find(events.begin(), events.end(), (SDL_EventType)e.type) == events.end())
			events.insert((SDL_EventType)e.type);

		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (keysDown.find(e.key.keysym.sym) != keysDown.end())
				keysHeld.insert(e.key.keysym.sym);
			else
				keysDown.insert(e.key.keysym.sym);
			break;

		case SDL_KEYUP:
			keysUp.insert(e.key.keysym.sym);

			keysDown.erase(e.key.keysym.sym);
			keysHeld.erase(e.key.keysym.sym);

			break;

		default:
			break;
		}
	}
}

/* ----- KEY FUNCTIONS ----- */

bool InputManager::GetKeyPressed(SDL_Keycode key)
{
	return (keysDown.find(key) != keysDown.end());
}

bool InputManager::GetKeyReleased(SDL_Keycode key)
{
	return (keysUp.find(key) != keysUp.end());
}

bool InputManager::GetKeyHeld(SDL_Keycode key)
{
	return (keysHeld.find(key) != keysHeld.end());
}

bool InputManager::GetEvent(SDL_EventType eventType)
{
	return (events.find(eventType) != events.end());
}

/* ----- AXIS FUNCTIONS ----- */

int  InputManager::GetAxis(std::string name)
{
	int rValue = 0;

	if (axes.find(name) != axes.end())
	{
		for each (SDL_Keycode key in axes[name].positiveKeys)
		{
			if (GetKeyPressed(key) || GetKeyHeld(key))
			{
				rValue += 1;
				break;
			}
		}

		for each (SDL_Keycode key in axes[name].negativeKeys)
		{
			if (GetKeyPressed(key) || GetKeyHeld(key))
			{
				rValue -= 1;
				break;
			}
		}

		return rValue;
	}

	std::cerr << "Error: Axis " << "'" << name << "'" << " does not exist" << std::endl;
	return 0;
}

void InputManager::AddAxis(std::string name)
{
	axes[name] = axisKeys();
}

void InputManager::AddAxis(std::string name, SDL_Keycode positiveKey, SDL_Keycode negativeKey)
{
	axisKeys tempAxis;

	tempAxis.positiveKeys.push_back(positiveKey);
	tempAxis.negativeKeys.push_back(negativeKey);

	axes[name] = tempAxis;
}

void InputManager::BindKeyToAxis(std::string axis, axisEnd type, SDL_Keycode key)
{
	if (axes.find(axis) != axes.end())
	{
		if (type == AXIS_POSITIVE_END)
			axes[axis].positiveKeys.push_back(key);
		else
			axes[axis].negativeKeys.push_back(key);
	}
}

void InputManager::UnbindAllKeysFromAxis(std::string axis)
{
	axes[axis].positiveKeys.clear();
	axes[axis].negativeKeys.clear();
}

void InputManager::RebindAxis(std::string axis, axisEnd endToRebind, SDL_Keycode key)
{
	BindKeyToAxis(axis, endToRebind, key);
}

/* ----- ACTION FUNCTIONS ----- */

void InputManager::AddAction(std::string name)
{
	actions[name] = SDLK_UNKNOWN;
}

void InputManager::AddAction(std::string name, SDL_Keycode binding)
{
	actions[name] = binding;
}

void InputManager::RebindAction(std::string action, SDL_Keycode newBinding)
{
	actions[action] = newBinding;
}

void InputManager::UnbindAction(std::string action)
{
	RebindAction(action, SDLK_UNKNOWN);
}

bool InputManager::ActionPressed(std::string action)
{
	return GetKeyPressed(actions[action]);
}

bool InputManager::ActionReleased(std::string action)
{
	return GetKeyReleased(actions[action]);
}