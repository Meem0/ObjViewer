#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <memory>

class Model;

std::tr1::shared_ptr<Model> ParseObj(const char* file);

#endif
