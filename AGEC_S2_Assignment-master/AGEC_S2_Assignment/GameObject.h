#pragma once
#include <vector>
#include "HeadersGL.h"
#include "Component.h"
#include "Components.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	bool Logic();
	bool UpdateAll();
	void Render();

	virtual bool Update();

	virtual bool Init();
	virtual void Destroy();

	template<class T>
	T* GetComponent();

	template<class T>
	T* AddComponent();

	Transform* transform;

protected:
	std::vector<Component*> components;
	std::vector<GameObject*> children;
};

template<class T>
T* GameObject::GetComponent()
{
	for each (Component* c in components)
	{
		if (typeid(*c).name() == typeid(T).name())
			return (T*)c;
	}

	return nullptr;
}

template<class T>
T* GameObject::AddComponent()
{
	if (GetComponent<T>() != nullptr)
		return GetComponent<T>();

	T* temp = new T();

	if (!temp->Init())
		return nullptr;

	temp->gameObject = this;
	components.push_back(temp);

	return temp;
}
