#pragma once
#include "InputConst.h"
#include "../utils/ConsoleControl.h"
#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <map>
#include <functional>


class InputSystem
{
public:

	class KeyBinding
	{
		friend class InputSystem;
		public:
			typedef std::function<void()> OnKeyPress;
		private:
			int key;
			OnKeyPress _onKeyPress;

			KeyBinding(int key, OnKeyPress onKeyPress);
			~KeyBinding();

		
	}

	typedef std::list<KeyBinding*> KeyBindingList;
	typedef std::map<int,KeyBindingList> KeyBindingMap;

public:
		InputSystem();
		~InputSystem();

		KeyBinding* AddListener(int key, KeyBinding::OnKeyPress onKeyPress);
		void RemoveAndDeleteListener(KeyBinding* keyBinding);

		void StartListen();
		void StopListen();

private:
	std::mutex* _classMutex;
	KeyBindingMap* _keyBindingsMap;

	enum State
	{
		Starting = 0,
		Listening = 1,
		Stopping = 2,
		Stopped = 3
	};
	
	State _state= Stopped;

	void ListenLoop();

};

