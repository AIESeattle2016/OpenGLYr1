//////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Author: Terry Nguyen
// Date: 01/06/2015
// Brief: Program main entrypoint
//
//////////////////////////////////////////////////////////////////////////

#include <GL\glew.h>	// GLEW
#include <GL\wglew.h>	// this isn't actually needed yet

#include <GLFW\glfw3.h>	// GLFW

int main(int argc, char * argv[])
{
	// # WINDOW CREATION
	// Initialize GLFW
	if (!glfwInit())
	{
		// Failed to initialize GLFW, return -1 for error
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow * window;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	
	// Verify window creation
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	// # GAME LOGIC

	// loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Draw code goes here

		// swap front and back buffers
		glfwSwapBuffers(window);

		// poll for and process events
		glfwPollEvents();

		if (glfwGetKey(window,GLFW_KEY_ESCAPE))
		{
			break;
		}
	}

	// # PROGRAM SHUTDOWN

	glfwTerminate();
	return 0;
}