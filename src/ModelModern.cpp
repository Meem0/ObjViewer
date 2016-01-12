#include "Model.h"
#include "Draw.h"

#ifdef USE_VBO

namespace ObjViewer {

	using namespace std;
	using namespace VectorLib;

	struct Model::ModelImpl {
		vector<Vector3> verts;
		vector<unsigned int> faces;
	};

	Model::Model() : pImpl(new ModelImpl()) {}

	void Model::AddVert(const Vector3& vert)
	{
		pImpl->verts.push_back(vert);
	}

	void Model::AddFace(const vector<int>& face)
	{
		unsigned int v1 = 1;
		unsigned int v2 = 2;
		size_t size = face.size();

		// do a "triangle fan" for faces of order > 3
		while (v2 < size) {
			pImpl->faces.push_back(face[0]);
			pImpl->faces.push_back(face[v1++]);
			pImpl->faces.push_back(face[v2++]);
		}
	}

	const Vector3& Model::GetVert(unsigned int index) const
	{
		if (index >= pImpl->verts.size()) {
			throw out_of_range("vertex index out of range");
		}

		return pImpl->verts[index];
	}

	const std::vector<int>& Model::GetFace(unsigned int index) const
	{
		throw exception("GetFace not supported");
	}

	const Vector3* Model::GetVertArray() const
	{
		return &pImpl->verts.front();
	}

	const unsigned int* Model::GetFaceArray() const
	{
		return &pImpl->faces.front();
	}

	unsigned int Model::NumVerts() const
	{
		return pImpl->verts.size();
	}

	unsigned int Model::NumFaces() const
	{
		return pImpl->faces.size() / 3;
	}

}

#endif
