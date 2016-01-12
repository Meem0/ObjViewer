#include "Draw.h"

#include <Windows.h>
#include <gl/GL.h>
#include <vector>

#include "VectorLib.h"
#include "Model.h"
#include "Input.h"

namespace ObjViewer {

	using namespace std;
	using namespace VectorLib;

#ifndef USE_VBO

	Vector3 translate;
	Vector3 rotation;
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	void DrawModel(const Model& model)
	{
		glLoadIdentity();

		Input::HandleModelControls(translate, rotation, scale);

		glTranslatef(translate.x, translate.y, translate.z);
		glRotatef(rotation.x, 1.0f, 0, 0);
		glRotatef(rotation.y, 0, 1.0f, 0);
		glRotatef(rotation.z, 0, 0, 1.0f);

		unsigned int numFaces = model.NumFaces();
		for (unsigned int i = 0; i < numFaces; ++i) {
			const vector<int>& face = model.GetFace(i);

			glEnable(GL_POLYGON_OFFSET_FILL);
			glColor3f(0.7f, 0.7f, 0.7f);

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

			glDisable(GL_POLYGON_OFFSET_FILL);
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			for (unsigned int j = 0; j < face.size(); ++j) {
				const Vector3& vert = model.GetVert(face[j]);
				glVertex3f(vert.x, vert.y, vert.z);
			}
			glEnd();
		}
	}

#endif

}
