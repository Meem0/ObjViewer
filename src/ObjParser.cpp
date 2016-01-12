#include "ObjParser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Model.h"
#include "Draw.h" // for USE_VBO define

namespace ObjViewer {

	using namespace std;
	using namespace VectorLib;

	shared_ptr<Model> ParseObj(const char* file)
	{
		ifstream infile(file);
		if (!infile) {
			ostringstream msg;
			msg << file << " not found";
			throw exception(msg.str().c_str());
		}

		shared_ptr<Model> model(new Model());

		string line, type;
		while (getline(infile, line)) {
			istringstream iss(line);
			if (iss >> type) {
				if (!type.compare("v")) {
					Vector3 vert;
					iss >> vert.x;
					iss >> vert.y;
					iss >> vert.z;

					model->AddVert(vert);
				}
				else if (!type.compare("f")) {
					vector<int> face;
					int vertIndex;
					string token;
					while (iss >> token) {
						istringstream vss(token.substr(0, token.find('/')));
						vss >> vertIndex;
						face.push_back(vertIndex - 1);
					}
					model->AddFace(face);
				}
			}
		}

		return model;
	}

}
