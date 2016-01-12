#ifndef OBJ_FILE_H
#define OBJ_FILE_H

#include <memory>
#include <vector>
#include "VectorLib.h"

namespace ObjViewer {

	class Model
	{
	public:
		Model();

		void AddVert(const VectorLib::Vector3& vert);
		void AddFace(const std::vector<int>& face);

		const VectorLib::Vector3& GetVert(unsigned int index) const;
		const std::vector<int>& GetFace(unsigned int index) const;

		const VectorLib::Vector3* GetVertArray() const;
		const unsigned int* GetFaceArray() const;

		unsigned int NumVerts() const;
		unsigned int NumFaces() const;

	private:
		struct ModelImpl;
		std::shared_ptr<ModelImpl> pImpl;
	};

}

#endif
