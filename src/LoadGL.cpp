#include <Windows.h>
#include <gl\GL.h>
#include "LoadGL.h"

PFNGLGENBUFFERSPROC					glGenBuffers;
PFNGLBINDBUFFERPROC					glBindBuffer;
PFNGLBUFFERDATAPROC					glBufferData;
PFNGLCREATESHADERPROC				glCreateShader;
PFNGLSHADERSOURCEPROC				glShaderSource;
PFNGLCOMPILESHADERPROC				glCompileShader;
PFNGLGETSHADERIVPROC				glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
PFNGLCREATEPROGRAMPROC				glCreateProgram;
PFNGLATTACHSHADERPROC				glAttachShader;
PFNGLLINKPROGRAMPROC				glLinkProgram;
PFNGLGETPROGRAMIVPROC				glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
PFNGLUSEPROGRAMPROC					glUseProgram;
PFNGLDELETESHADERPROC				glDeleteShader;
PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
PFNGLGENVERTEXARRAYSPROC			glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC			glBindVertexArray;
PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
PFNGLUNIFORM4FPROC					glUniform4f;
PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;

namespace ObjViewer {
	void LoadGLFunctions()
	{
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	}
}
