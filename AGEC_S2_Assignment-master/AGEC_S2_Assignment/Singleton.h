#pragma once

template <class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (!_instance)
		{
			_instance = new T();
		}

		return _instance;
	}

	static void Destroy()
	{
		delete _instance;
		_instance = nullptr;
	}

private:
	static T* _instance;
};

template <class T> T*  Singleton<T>::_instance = nullptr;