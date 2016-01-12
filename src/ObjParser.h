#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <memory>

namespace ObjViewer {

	class Model;

	std::shared_ptr<Model> ParseObj(const char* file);

}

#endif
