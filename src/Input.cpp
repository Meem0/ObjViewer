#include "Input.h"

namespace Input {

	bool keys[256];

	bool IsKeyDown(int key)
	{
		return keys[key];
	}

	void HandleKeyEvent(bool isPressed, int key)
	{
		keys[key] = isPressed;
	}

	KeyEventHandler GetKeyEventHandler()
	{
		return HandleKeyEvent;
	}

}
