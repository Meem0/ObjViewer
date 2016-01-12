#ifndef SHADER_H
#define SHADER_H

#include <Windows.h>
#include <gl\GL.h>
#include <memory>

namespace ObjViewer {

	class Shader {
	public:
		Shader();
		// constructor that calls Compile
		Shader(const char* vertPath, const char* fragPath);

		// reads a vertex and fragment shader from files at the given paths
		// compiles and links the shaders into a program
		void Compile(const char* vertPath, const char* fragPath);

		// does glUseProgram on the held program
		// must have called Compile (or used the Compile constructor)
		void Use();

		GLuint GetProgram() const;

	private:
		struct ShaderImpl;
		std::shared_ptr<ShaderImpl> pImpl;
	};

}

#endif
