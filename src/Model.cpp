#include "Model.h"
#include <vector>

using namespace std;

struct Model::ModelImpl
{
	vector<Vector3> verts;
	vector<vector<int>> faces;
};

Model::Model()
	: pImpl(new ModelImpl())
{}

void Model::AddVert(const Vector3& vert)
{
	pImpl->verts.push_back(vert);
}

void Model::AddFace(const vector<int>& face)
{
	pImpl->faces.push_back(face);
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
	if (index >= pImpl->faces.size()) {
		throw out_of_range("face index out of range");
	}
	return pImpl->faces[index];
}

unsigned int Model::NumVerts() const
{
	return pImpl->verts.size();
}

unsigned int Model::NumFaces() const
{
	return pImpl->faces.size();
}
