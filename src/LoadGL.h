#ifndef LOAD_GL_H
#define LOAD_GL_H

#include "glext.h"

extern PFNGLGENBUFFERSPROC				glGenBuffers;
extern PFNGLBINDBUFFERPROC				glBindBuffer;
extern PFNGLBUFFERDATAPROC				glBufferData;
extern PFNGLCREATESHADERPROC			glCreateShader;
extern PFNGLSHADERSOURCEPROC			glShaderSource;
extern PFNGLCOMPILESHADERPROC			glCompileShader;
extern PFNGLGETSHADERIVPROC				glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC		glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC			glCreateProgram;
extern PFNGLATTACHSHADERPROC			glAttachShader;
extern PFNGLLINKPROGRAMPROC				glLinkProgram;
extern PFNGLGETPROGRAMIVPROC			glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC		glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC				glUseProgram;
extern PFNGLDELETESHADERPROC			glDeleteShader;
extern PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
extern PFNGLGENVERTEXARRAYSPROC			glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC			glBindVertexArray;
extern PFNGLGETUNIFORMLOCATIONPROC		glGetUniformLocation;
extern PFNGLUNIFORM4FPROC				glUniform4f;
extern PFNGLUNIFORMMATRIX4FVPROC		glUniformMatrix4fv;

namespace ObjViewer {
	void LoadGLFunctions();
}

#endif
