#include "Input.h"

#include <Windows.h>

#include "VectorLib.h"

namespace Input {

	using namespace ObjViewer;
	using namespace VectorLib;

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

	const static float TRANS_SPEED = 0.2f;
	const static float ROT_SPEED = 3.0f;
	const static float SCALE_SPEED = 0.01f;
	char rotAxis = 'x';

	void HandleModelControls(Vector3& trans, Vector3& rot, Vector3& scale)
	{
		float transDelta = TRANS_SPEED;
		float rotDelta = ROT_SPEED;
		float scaleDelta = SCALE_SPEED;

		if (IsKeyDown(VK_SHIFT)) {
			transDelta *= 10.0f;
			rotDelta *= 5.0f;
			scaleDelta *= 10.0f;
		}

		if (IsKeyDown('W')) {
			trans.y += transDelta;
		}
		if (IsKeyDown('S')) {
			trans.y -= transDelta;
		}
		if (IsKeyDown('A')) {
			trans.x -= transDelta;
		}
		if (IsKeyDown('D')) {
			trans.x += transDelta;
		}
		if (IsKeyDown('R')) {
			trans.z -= transDelta;
		}
		if (IsKeyDown('F')) {
			trans.z += transDelta;
		}

		if (IsKeyDown('X')) {
			rotAxis = 'x';
		}
		if (IsKeyDown('Y')) {
			rotAxis = 'y';
		}
		if (IsKeyDown('Z')) {
			rotAxis = 'z';
		}

		int rotDir = 0;
		if (IsKeyDown('Q')) {
			rotDir = -1;
		}
		if (IsKeyDown('E')) {
			rotDir = 1;
		}
		if (rotDir) {
			rotDelta *= static_cast<float>(rotDir);
			switch (rotAxis) {
			case 'x': rot.x += rotDelta; break;
			case 'y': rot.y += rotDelta; break;
			case 'z': rot.z += rotDelta; break;
			}
		}

		if (IsKeyDown('C')) {
			scale.x = scale.y = scale.z = scale.x - scaleDelta * scale.x;
		}
		if (IsKeyDown('V')) {
			scale.x = scale.y = scale.z = scale.x + scaleDelta * scale.x;
		}
	}

}
