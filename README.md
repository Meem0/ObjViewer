# ObjViewer

To compile in Visual Studio, add glu32.lib and opengl32.lib to Project Settings -> Linker -> Input -> Additional Dependencies.

WASD to translate

QE to rotate (x/y/z to change axis of rotation)

CV to scale


Hold shift to speed up any of the above


If USE_VBO (in Draw.h) is defined, modern GL will be used: shaders, VBOs, and the like.  Otherwise, it will use glBegin(), glVertex3f(), etc..
