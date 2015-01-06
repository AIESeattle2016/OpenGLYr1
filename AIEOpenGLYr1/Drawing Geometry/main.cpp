//////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Author: Terry Nguyen
// Date: 01/06/2015
// Brief: Program main entrypoint
//
//////////////////////////////////////////////////////////////////////////

#include <GLFW\glfw3.h>

int main(int argc, char * argv[])
{
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

	// loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Draw code goes here

		// swap front and back buffers
		glfwSwapBuffers(window);

		// poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}