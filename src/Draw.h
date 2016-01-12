#ifndef DRAW_H
#define DRAW_H

//#define USE_VBO

namespace ObjViewer {

	class Model;

	void DrawModel(const Model& model);

#ifdef USE_VBO
	void InitVBO(const Model& model);
#endif

}

#endif
