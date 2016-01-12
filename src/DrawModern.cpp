#include "Draw.h"

#include <Windows.h>
#include <time.h>
#include <gl\GL.h>
#include <iostream>
#include <memory>
#include <vector>

#include "LoadGL.h"
#include "Model.h"
#include "Input.h"
#include "Shader.h"
#include "VectorLib.h"

namespace ObjViewer {

	using namespace std;
	using namespace VectorLib;

#ifdef USE_VBO

	Shader shader;
	GLuint VBO, VAO, EBO;

	void InitVBO(const Model& model)
	{
		shader.Compile("src/shaders/vertexShader.vert", "src/shaders/fragmentShader.frag");

		// create a VAO and bind it
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// set up and fill a VBO with the vertices
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.NumVerts() * 3, model.GetVertArray(), GL_DYNAMIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model.NumFaces() * 3, model.GetFaceArray(), GL_DYNAMIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

		// unbind the VAO
		glBindVertexArray(0);
	}

	Matrix4 transScaleMat;

	Vector3 translate;
	Vector3 rotation;
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	const static float ROT_MOD = 0.01f;

	void DrawModel(const Model& model)
	{
		Input::HandleModelControls(translate, rotation, scale);

		transScaleMat(0, 3) = translate.x;
		transScaleMat(1, 3) = translate.y;
		transScaleMat(2, 3) = translate.z;

		transScaleMat(0, 0) = scale.x;
		transScaleMat(1, 1) = scale.y;
		transScaleMat(2, 2) = scale.z;

		Matrix4 modelMat =
			RotMatrix(rotation.x * ROT_MOD, Vector3(1.0f, 0, 0)) *
			RotMatrix(rotation.y * ROT_MOD, Vector3(0, 1.0f, 0)) *
			RotMatrix(rotation.z * ROT_MOD, Vector3(0, 0, 1.0f)) *
			transScaleMat;

		shader.Use();
		GLuint program = shader.GetProgram();

		GLint uniformLocation = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, modelMat.GetColumnMajor());

		GLint colourUniLocation = glGetUniformLocation(program, "uniColour");
		glUniform4f(colourUniLocation, 0.7f, 0.7f, 0.7f, 1.0f);

		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, model.NumFaces() * 3, GL_UNSIGNED_INT, 0);

		glUniform4f(colourUniLocation, 0, 0, 0, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, model.NumFaces() * 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

#endif

}
