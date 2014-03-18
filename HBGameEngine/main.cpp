//////////////////////////////////////
//File:              <main.cpp>
//Author:            <Hunter Bergerud>
//Date Created:      <3/3/14>
//Date Modified:     <3/10/14>
//Brief:             <Main Code>
//////////////////////////////////////
#define GLFW_DLL
#include <GL\glew.h>
#include <stdio.h>
#include "FontManager.h"
//Make a function that gets the window size
void glfw_window_size_callback (GLFWwindow* window, int width, int height) 
{
	g_gl_width = width;
	g_gl_height = height;
}
//Make a function that shows an error
void glfw_error_callback (int error, const char* description) 
{
	fputs (description, stderr);
	gl_log (description, __FILE__, __LINE__);
}
int main()
{
	//Reset Delta Time
	resetDeltaTime();
	//Make a char stack caled message
	char message[256];
	//Print out message and assert it
	sprintf (message, "starting GLFW %s", glfwGetVersionString ());
	assert (gl_log (message, __FILE__, __LINE__));
	//Set error callback
	glfwSetErrorCallback (glfw_error_callback);
	//If glfwInit cannot be found
	if(!glfwInit())
	{
		//Print an error saying the program couldn't start
		fprintf (stderr,"ERROR: could not start GLFW3\n");
		return 1;
	}
	//Make a window hint
	glfwWindowHint (GLFW_SAMPLES, 4);
	//Make a GLFWmonitor pointer called mon
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	//Make a constant GLFWvidmode
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	//Create a GLFW window
	GLFWwindow* window = glfwCreateWindow 
	(
		vmode->width, vmode->height, "Extended GL Init",NULL/* mon*/, NULL
	);
	//Set the window size
	glfwSetWindowSize(window, g_gl_width, g_gl_height);
	//If window cannot be found
	if (!window) 
	{
		//Print a error saying the window cannot open with GLFW and terminate glfw
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	//Call glfwMakeContextCurrent with window
	glfwMakeContextCurrent(window);
	//Make glewExperimental equal GL_TRUE
	glewExperimental = GL_TRUE;
	//Call glewInit
	glewInit();
	//Make a GLubyte poniter for renderer and version and print them out
	const GLubyte* renderer = glGetString (GL_RENDERER);
	const GLubyte* version = glGetString (GL_VERSION);
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);
	//Enable GL_DEPTH_TEST
	glEnable (GL_DEPTH_TEST);
	//Call DepthFunc with GL_LESS
	glDepthFunc (GL_LESS);
	//Make a new Matrix4 Ortho
	Ortho =  new tbyte::Matrix4();
	//Call Orthographic with the required data
	Orthographic(0,g_gl_width,g_gl_height,0,0,-1,Ortho);
	////Make a AnimatedSprite pointer with the required data
	AnimatedSprite * charizard = new AnimatedSprite("resources/Charizard.xml",window);
	//Make a new FontManager and Load the font
	FontManager * fntMon = new FontManager();
	fntMon->LoadFont("resources/NESish.xml");
	//While the window is open
	while (!glfwWindowShouldClose (window)) 
	{
		//Enable GL_ALPHA_TEST
		glEnable(GL_ALPHA_TEST);
		//Call glAlphaFunc
		glAlphaFunc(GL_GREATER, .5);
		//Enable GL_CULL_FACE
		glEnable (GL_CULL_FACE);
		//Call CullFace and FrontFace
		glCullFace (GL_BACK);
		glFrontFace (GL_CW);
		//Call glClear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Call Viewport with the required data
		glViewport (0, 0, g_gl_width, g_gl_height);
		//Update the AnimatedSprite
		charizard->Update();
		//Draw the text with the FontManager
		fntMon->DrawString("Pokemon! Gotta Catch them All!",Vector2(g_gl_height/2,6),1);
		//Make a new char stack called tmp
		char tmp[128];
		//Print out the frames per second
		sprintf (tmp, "opengl @ fps: %.2f", fps);
		//Set the window title with the required data
		glfwSetWindowTitle (window, tmp);
		//Call glfwPollEvents
		glfwPollEvents ();
		//Call glfwSwapBuffers
		glfwSwapBuffers (window);
		//Reset Delta Time
		resetDeltaTime();
		//If the user presses the Esc Key
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) 
		{
			//Cloase the window
			glfwSetWindowShouldClose (window, 1);
		}
	}
	//Terminate glfw
	glfwTerminate();
	return 0;
}