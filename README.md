# ObjViewer

To compile in Visual Studio, add glu32.lib and opengl32.lib to Project Settings -> Linker -> Input -> Additional Dependencies.

Test .obj files: http://people.sc.fsu.edu/~jburkardt/data/obj/obj.html

WASD to translate

QE to rotate (x/y/z to change axis of rotation)

RF to zoom in / out

Hold shift to speed up any of the above


If USE_VBO (in Draw.h) is defined, modern GL will be used: shaders, VBOs, and the like.  Otherwise, it will use glBegin(), glVertex3f(), etc..
