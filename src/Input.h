#ifndef INPUT_H
#define INPUT_H

namespace ObjViewer {
	namespace VectorLib {
		struct Vector3;
	}
}

namespace Input {

	// is the key currently held down
	bool IsKeyDown(int key);

	typedef void(*KeyEventHandler)(bool, int);
	// get the function which receives key press/release events
	KeyEventHandler GetKeyEventHandler();

	void HandleModelControls(ObjViewer::VectorLib::Vector3& trans,
		ObjViewer::VectorLib::Vector3& rot,
		ObjViewer::VectorLib::Vector3& scale);
}

#endif
