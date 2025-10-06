#include "InputSystem.h"
#include "../utils/ConsoleControl.h"
using CC = ConsoleControl;

InputSystem::KeyBinding::KeyBinding(int key, OnKeyPress onKeyPress)
{
	_key = key;
	_onKeyPress = onKeyPress;
}

InputSystem::KeyBinding::~KeyBinding()
{

}

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{
	for( std::pair<int,KeyBindingList> pair : _keyBindingsMap)
	{
		KeyBindingList bindingList = pair.second();
		for (KeyBinding* binding: bindingList)
		{
			delete binding;
		}
		bindingList.clear();
	}

	_keyBindingsMap->clear();
}

KeyBinding* InputSystem::AddListener(int key, KeyBinding::OnKeyPress onKeyPress)
{
	_classMutex.lock();

	if (_keyBindingMap.find(key) == _keyBindingsMap->end())
	{
		_keyBindingsMap[key] = KeyBindingList();
	}

	KeyBinding* keyBinding = new KeyBinding(key, onKeyPress);
	_keyBindingsMap[key].push_back(keyBinding);
	_classMutex.unlock();
	return keyBinding;
}

void InputSystem::RemoveAndDeleteListener(KeyBinding* keyBinding)
{
	int key = keyBinding->_key;
	_classMutex.lock();
	if (_keyBindingMap.find(key) != _keyBindingsMap->end())
	{
		KeyBindingList list = _keyBindingsMap[key];
		list.remove(keyBinding);
		if (list.size()<=0)
		{
			_keyBindingsMap.erase(key);
		}
	}
	_classMutex.unlock();
}

void InputSystem::StartListen()
{
	_classMutex.lock();
	if (_state != Stopped)
	{
		_classMutex.unlock();
		return;
	}
	_state = Starting;

	std::thread* listenLoopThread = new std::thread(&InputSystem::ListenLoop, this);
	listenLoopThread->detach();
	_classMutex.unlock();
}

void InputSystem::StopListen()
{
	_classMutex.lock();
	if (_state != Listening)
	{
		_classMutex.unlock();
		return;
	}
	_state = Stopping;
	_classMutex.unlock();
}

void InputSystem::ListenLoop()
{
	_classMutex.lock();
	_state = Listening;
	State currentState = _state;

	CC::ClearKeyBuffer();
	while (currentState==Listening)
	{
		int key = CC::ReadNextKey();
		if (key != 0)
		{
			_classMutex->lock();
			if (_keyBindingsMap->find(key) != _keyBindingsMap->end())
			{
				KeyBindingList list = _keyBindingsMap(key);
				for (KeyBinding* binding :list)
				{
					std::thread* onKeyPressThread = new std::thread(binding->_onKeyPress);
					onKeyPressThread->detach();
				}
			}
		}

		_classMutex.lock();
		currentState = _state;
		_classMutex.unlock();
	}
	_classMutex.lock();
	
	if (_state == Stopping)
	{
		_state = Stopped;
	}
	_classMutex.unlock();
	
}
