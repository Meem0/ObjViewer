#include "Draw.h"

#include <Windows.h>
#include <gl/GL.h>
#include <vector>

#include "VectorLib.h"
#include "Model.h"
#include "Input.h"

using namespace std;

Vector3 translate;
Vector3 rotation;
Vector3 scale = { 1.0f, 1.0f, 1.0f };
const static float TRANS_SPEED = 0.2f;
const static float ROT_SPEED = 3.0f;
const static float SCALE_SPEED = 0.05f;
char rotDir = 'x';

void Controls()
{
	float transDelta = TRANS_SPEED;
	if (Input::IsKeyDown(VK_SHIFT)) {
		transDelta *= 10.0f;
	}

	if (Input::IsKeyDown('W')) {
		translate.y += transDelta;
	}
	if (Input::IsKeyDown('S')) {
		translate.y -= transDelta;
	}
	if (Input::IsKeyDown('A')) {
		translate.x -= transDelta;
	}
	if (Input::IsKeyDown('D')) {
		translate.x += transDelta;
	}
	if (Input::IsKeyDown('R')) {
		translate.z -= transDelta;
	}
	if (Input::IsKeyDown('F')) {
		translate.z += transDelta;
	}

	if (Input::IsKeyDown('X')) {
		rotDir = 'x';
	}
	if (Input::IsKeyDown('Y')) {
		rotDir = 'y';
	}
	if (Input::IsKeyDown('Z')) {
		rotDir = 'z';
	}

	int rotAmount = 0;
	if (Input::IsKeyDown('Q')) {
		rotAmount = -1;
	}
	if (Input::IsKeyDown('E')) {
		rotAmount = 1;
	}
	if (rotAmount) {
		float delta = static_cast<float>(rotAmount) * ROT_SPEED;
		switch (rotDir) {
		case 'x': rotation.x += delta; break;
		case 'y': rotation.y += delta; break;
		case 'z': rotation.z += delta; break;
		}
	}

	bool scaleChange = false;
	if (Input::IsKeyDown('C')) {
		scale.x = scale.y = scale.z = scale.x - SCALE_SPEED;
		scaleChange = true;
	}
	if (Input::IsKeyDown('V')) {
		scale.x = scale.y = scale.z = scale.x + SCALE_SPEED;
		scaleChange = true;
	}
	if (scaleChange) {
		glScalef(scale.x, scale.y, scale.z);
	}
}

const static float COLOUR_MIN = 0.5f;
const static float COLOUR_MAX = 0.65f;
const static int NUM_SHADES = 50;

Vector3 ChooseColour(unsigned int index)
{
	Vector3 ret = { 0, 0, 0 };

	//float value = (float)((index % NUM_SHADES) + NUM_SHADES * 2) / (float)(NUM_SHADES * 4);

	float shadeDelta = (COLOUR_MAX - COLOUR_MIN) / (float)NUM_SHADES;
	float value = COLOUR_MIN + (float)(index % NUM_SHADES) * shadeDelta;

	ret.x = ret.y = ret.z = value;

	return ret;
}

inline void DrawVertex(const Vector3& vert)
{
	glVertex3f(vert.x, vert.y, vert.z);
}

void DrawModel(const Model& model)
{
	glLoadIdentity();

	Controls();
	
	glTranslatef(translate.x, translate.y, translate.z);
	glRotatef(rotation.x, 1.0f, 0, 0);
	glRotatef(rotation.y, 0, 1.0f, 0);
	glRotatef(rotation.z, 0, 0, 1.0f);

	unsigned int numFaces = model.NumFaces();
	for (unsigned int i = 0; i < numFaces; ++i) {
		const vector<int>& face = model.GetFace(i);

		Vector3 colour = ChooseColour(i);
		glColor3f(colour.x, colour.y, colour.z);

		switch (face.size()) {
		case 3: glBegin(GL_TRIANGLES); break;
		case 4: glBegin(GL_QUADS); break;
		default: glBegin(GL_POLYGON); break;
		}

		for (unsigned int j = 0; j < face.size(); ++j) {
			const Vector3& vert = model.GetVert(face[j]);
			glVertex3f(vert.x, vert.y, vert.z);
		}

		glEnd();
	}
}
