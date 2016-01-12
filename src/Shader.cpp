#include "Shader.h"

#include <Windows.h>
#include <gl\GL.h>
#include "LoadGL.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ObjViewer {

	using namespace std;

	// RAII for shaders
	class ShaderHolder {
	public:
		ShaderHolder() : _shader(0) {}
		ShaderHolder(GLuint shader) : _shader(shader) {}
		~ShaderHolder() {
			if (_shader != 0) {
				glDeleteShader(_shader);
			}
		}
		GLuint Get() {
			return _shader;
		}
		void Reset(GLuint shader) {
			_shader = shader;
		}
	private:
		// disable copying / assignment
		ShaderHolder(const ShaderHolder&);
		ShaderHolder& operator=(const ShaderHolder&);

		GLuint _shader;
	};

	struct Shader::ShaderImpl {
		GLuint program;
	};

	Shader::Shader() : pImpl(new ShaderImpl()) {}

	Shader::Shader(const char * vertPath, const char * fragPath)
		: pImpl(new ShaderImpl())
	{
		Compile(vertPath, fragPath);
	}

	void GetText(string& outText, const char* path)
	{
		ifstream inFile(path);
		if (inFile.fail()) {
			ostringstream oss("file not found: ");
			oss << path;
			throw exception(oss.str().c_str());
		}

		string line;
		ostringstream outString;

		while (getline(inFile, line)) {
			if (!line.empty()) {
				outString << line << std::endl;
			}
		}

		outText = outString.str();
	}

	void CompileShader(GLuint shader, const GLchar* source)
	{
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		// error check
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);

			ostringstream oss("shader compilation failed: ");
			oss << infoLog;

			throw exception(oss.str().c_str());
		}
	}

	void Shader::Compile(const char * vertPath, const char * fragPath)
	{
		string vertText, fragText;

		GetText(vertText, vertPath);	// read vertex shader file
		ShaderHolder vertexShader(glCreateShader(GL_VERTEX_SHADER));	// create OpenGL shader object
		CompileShader(vertexShader.Get(), vertText.c_str());	// compile the shader

		// do the same for the fragment shader
		GetText(fragText, fragPath);
		ShaderHolder fragmentShader(glCreateShader(GL_FRAGMENT_SHADER));
		CompileShader(fragmentShader.Get(), fragText.c_str());

		GLuint& program = pImpl->program;
		program = glCreateProgram();
		glAttachShader(program, vertexShader.Get());
		glAttachShader(program, fragmentShader.Get());
		glLinkProgram(program);

		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetProgramInfoLog(program, 512, NULL, infoLog);

			ostringstream oss("program linking failed: ");
			oss << infoLog;

			throw exception(oss.str().c_str());
		}
	}

	void Shader::Use()
	{
		glUseProgram(pImpl->program);
	}

	GLuint Shader::GetProgram() const
	{
		return pImpl->program;
	}

}
