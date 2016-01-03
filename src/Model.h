#ifndef OBJ_FILE_H
#define OBJ_FILE_H

#include <memory>
#include <vector>
#include "VectorLib.h"

class Model
{
public:
	Model();

	void AddVert(const Vector3& vert);
	void AddFace(const std::vector<int>& face);

	const Vector3& GetVert(unsigned int index) const;
	const std::vector<int>& GetFace(unsigned int index) const;

	unsigned int NumVerts() const;
	unsigned int NumFaces() const;

private:
	struct ModelImpl;
	std::tr1::shared_ptr<ModelImpl> pImpl;
};

#endif
