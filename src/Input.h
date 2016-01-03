#ifndef INPUT_H
#define INPUT_H

namespace Input {

	// is the key currently held down
	bool IsKeyDown(int key);

	typedef void(*KeyEventHandler)(bool, int);
	// get the function which receives key press/release events
	KeyEventHandler GetKeyEventHandler();

}

#endif
