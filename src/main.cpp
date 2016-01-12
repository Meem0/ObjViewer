// http://nehe.gamedev.net/tutorial/creating_an_opengl_window_(win32)/13001/

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include "ObjParser.h"
#include "Draw.h"
#include "Model.h"
#include "Input.h"
#include "LoadGL.h"

HGLRC		hRC = NULL;		// permanent rendering context
HDC			hDC = NULL;		// private Graphics Device Interface device context
HWND		hWnd = NULL;	// window handle
HINSTANCE	hInstance;		// application instance

bool active = TRUE;		// is the window active (not minimized)
bool fullscreen = FALSE;
bool wasFullscreenToggled = FALSE;	// ensure fullscreen is only toggled once per key press
Input::KeyEventHandler keyEventHandler;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// resize and initialize the GL window
GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
	// prevent divide by zero
	if (height == 0) {
		height = 1;
	}

	// reset the viewport
	glViewport(0, 0, width, height);

	// reset the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		45.0f,									// field of view
		(GLdouble)width / (GLdouble)height,		// aspect ratio
		0.1f,									// near clipping plane
		1000.0f);								// far clipping plane

	// reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// OpenGL setup
int InitGL(GLvoid)
{
	// load modern GL functions
	ObjViewer::LoadGLFunctions();

	// smooth shading
	glShadeModel(GL_SMOOTH);

	// clear to black
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	// setup depth buffer
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// best perspective calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_DONT_CARE);

	// avoid "z-fighting" with wireframe
	glPolygonOffset(1.0f, 1.0f);

	return TRUE;
}

std::shared_ptr<ObjViewer::Model> model;

// draw the scene
int DrawGLScene(GLvoid)
{
	// clear the screen and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ObjViewer::DrawModel(*model);

	return TRUE;
}

// kill the window, showing pop-up messages on error
GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen) {
		// switch back to the desktop, using Windows' default values
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC) {
		// try to detach the rendering context from the device context
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(
				NULL,
				L"Error releasing DC and RC",
				L"SHUTDOWN ERROR",
				MB_OK | MB_ICONINFORMATION);
		}

		// try to delete the rendering context
		if (!wglDeleteContext(hRC)) {
			MessageBox(
				NULL,
				L"Error releasing RC",
				L"SHUTDOWN ERROR",
				MB_OK | MB_ICONINFORMATION);
		}

		hRC = NULL;
	}

	// try to release the device context
	if (hDC && !ReleaseDC(hWnd, hDC)) {
		MessageBox(
			NULL,
			L"Error releasing DC",
			L"SHUTDOWN ERROR",
			MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(
			NULL,
			L"Error destroying window",
			L"SHUTDOWN ERROR",
			MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass(L"OpenGL", hInstance)) {
		MessageBox(
			NULL,
			L"Error unregistering class",
			L"SHUTDOWN ERROR",
			MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}


BOOL CreateGLWindow(wchar_t* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle; // extended window style
	DWORD dwStyle; // normal window style

	// set up the rectangle defining the window's bounds
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;

	// get an instance for the window
	hInstance = GetModuleHandle(NULL);

	// fill out properties of the window class structure
	// redraw on move / resize, DC is private to this application
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc; // attach our message handler
	wc.cbClsExtra = 0; // nothing
	wc.cbWndExtra = 0; // nothing
	wc.hInstance = hInstance; // attach the hInstance we got earlier
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // default icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // arrow cursor
	wc.hbrBackground = NULL; // no background
	wc.lpszMenuName = NULL; // no menu
	wc.lpszClassName = L"OpenGL";

	// try to register the window class we just filled out
	if (!RegisterClass(&wc)) {
		MessageBox(
			NULL,
			L"Error registering window class",
			L"ERROR",
			MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}

	// attempt to enter fullscreen mode
	if (fullscreen) {
		DEVMODE dmScreenSettings; // device mode
		// initialize it to 0
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		// size of the structure
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		// screen size
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		// bits per pixel
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// try to apply the fullscreen settings
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)
			!= DISP_CHANGE_SUCCESSFUL) {
			if (MessageBox(
					NULL,
					L"Error applying the requested fullscreen mode.\n"
					L"Want to try windowed mode?  (Will close otherwise)",
					L"ERROR",
					MB_YESNO | MB_ICONEXCLAMATION)
				== IDYES) {
				fullscreen = FALSE;
			}
			else {
				return FALSE;
			}
		}
	}

	// set a few more styles, if fullscreen mode was successful
	if (fullscreen) {
		// this window extended style forces a top-level window
		// onto the taskbar when ours is visible
		dwExStyle = WS_EX_APPWINDOW;
		// this window style makes our window borderless
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	// windowed mode
	else {
		// window extended style: appwindow as in fullscreen,
		// plus windowedge, which makes it look more 3D
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		// this window style gives a title bar, resizeable borders, etc.
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	// adjusts the window size, ignoring the borders
	// (does nothing in fullscreen mode)
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(
			dwExStyle,	// extended style
			L"OpenGL",	// class name
			title,		// window title
			WS_CLIPSIBLINGS |  // these window styles are required for OpenGL.
			WS_CLIPCHILDREN |  // they prevent other windows from drawing in or over our window.
			dwStyle,	// window style
			0, 0,		// window position
			WindowRect.right - WindowRect.left,	// width
			WindowRect.bottom - WindowRect.top,	// height
			NULL,	// no parent window
			NULL,	// no menu
			hInstance,	// instance
			NULL))) {	// arguments to WM_CREATE
		KillGLWindow();
		MessageBox(NULL, L"Error creating window", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// set up a pixel format, which specifies properties of the OpenGL drawing surface
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this PFD
		1,	// version number
		PFD_DRAW_TO_WINDOW |	// the buffer can draw to a window
		PFD_SUPPORT_OPENGL |	// the buffer supports OpenGL
		PFD_DOUBLEBUFFER,	// the buffer is double-buffered
		PFD_TYPE_RGBA,	// use RGBA pixels
		(BYTE)bits,	// number of colour bitplanes in each colour buffer (for RGBA, = size of colour buffer)
		0, 0, 0, 0, 0, 0, 0, 0,	// colour / alpha bitplanes and shift counts ignored
		0, 0, 0, 0, 0,	// accumulation bits ignored
		16,	// depth of the depth (z-axis) buffer
		0, 0,	// stencil / auxiliary buffers ignored
		PFD_MAIN_PLANE,	// number of overlay and underlay planes
		0, 0, 0, 0	// reserved, layer/visible/damage masks ignored
	};

	// try to get a device context
	if (!(hDC = GetDC(hWnd))) {
		KillGLWindow();
		MessageBox(NULL, L"Error getting DC", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// ask Windows for a suitable pixel format
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
		KillGLWindow();
		MessageBox(NULL, L"Error finding pixel format", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// try to set the pixel format
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
		KillGLWindow();
		MessageBox(NULL, L"Error setting pixel format", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// try to create a rendering context
	if (!(hRC = wglCreateContext(hDC))) {
		KillGLWindow();
		MessageBox(NULL, L"Error creating rendering context", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// try to activate the rendering context
	if (!wglMakeCurrent(hDC, hRC)) {
		KillGLWindow();
		MessageBox(NULL, L"Error activating rendering context", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);	// show the window
	SetForegroundWindow(hWnd);	// move the window to the front, increasing its priority
	SetFocus(hWnd);	// give the window keyboard focus
	ResizeGLScene(width, height);	// resize and initialize the window

	// try to initialize the newly-created window
	if (!InitGL()) {
		KillGLWindow();
		MessageBox(NULL, L"Error initializing OpenGL", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}


// message handler
LRESULT CALLBACK WndProc(HWND hWnd, // window handle
	UINT uMsg,	// message
	WPARAM wParam,	// additional message information
	LPARAM lParam)	// additional message information
{
	switch (uMsg) {
	case WM_ACTIVATE: {	// window activated
		// set active to false if the window was minimized
		active = !HIWORD(wParam);
		return 0;
	}
	case WM_SYSCOMMAND: {	// syscall
		// interrupt any attempts to start a screensaver or montor powersave
		if (wParam == SC_SCREENSAVE ||
			wParam == SC_MONITORPOWER) {
			return 0;
		}
		break;
	}
	case WM_CLOSE: {	// window closed
		PostQuitMessage(0);	// send a quit message
		return 0;
	}
	case WM_KEYDOWN: {	// key pressed
		keyEventHandler(true, wParam);
		return 0;
	}
	case WM_KEYUP: {	// key released
		keyEventHandler(false, wParam);
		return 0;
	}
	case WM_SIZE: {	// window resized
		ResizeGLScene(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	}

	// pass unhandled messages to Windows
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// from https://www.gamedev.net/topic/509479-routing-stdout-to-windowconsole
void MakeConsole()
{
#ifdef _DEBUG
	AllocConsole();

	FILE *outstream_ptr;
	freopen_s(&outstream_ptr, "CONOUT$", "wb", stdout);
#endif
}


int WINAPI WinMain(HINSTANCE hInstance,	// handle to this instance
	HINSTANCE hPrevInstance,	// handle to previous instance (always NULL)
	LPSTR lpCmdLine,	// command line parameters
	int nCmdShow)	// how the window is shown (maximized, minimized, etc.)
{
	MakeConsole();
	keyEventHandler = Input::GetKeyEventHandler();

	MSG msg;	// Windows message structure
	BOOL done = FALSE;	// loop flag
	
	// try to create the window
	if (!CreateGLWindow(L"ObjViewer", 640, 480, 16, fullscreen)) {
		return 0;
	}

	if (__argc < 2) {
		std::cout << "ERROR: no object file specified in command line parameters" << std::endl;
		return 0;
	}
	const char* inputFile = __argv[1];

	try {
		model = ObjViewer::ParseObj(inputFile);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
		return 0;
	}

#ifdef USE_VBO
	ObjViewer::InitVBO(*model);
#endif

	// main loop
	while (!done) {
		// check for any waiting messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// quit message
			if (msg.message == WM_QUIT) {
				done = TRUE;
			}
			// deal with other messages if we're not quitting
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// no messages
		else {
			if (active) {
				// quit if escape is pressed
				if (Input::IsKeyDown(VK_ESCAPE)) {
					done = TRUE;
				}
				// draw the scene
				else {
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}

			if (wasFullscreenToggled) {
				wasFullscreenToggled = Input::IsKeyDown(VK_F1);
			}
			// toggle fullscreen
			else if (Input::IsKeyDown(VK_F1)) {
				wasFullscreenToggled = TRUE;

				KillGLWindow();	// destroy the window
				fullscreen = !fullscreen;	// toggle the fullscreen flag
											// attempt to recreate the window
				if (!CreateGLWindow(L"ObjViewer", 640, 480, 16, fullscreen)) {
					return 0;
				}
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}
