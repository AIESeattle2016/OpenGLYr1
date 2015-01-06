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

#include <Utilities.h>	// CreateProgram...

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
	window = glfwCreateWindow(1024, 720, "Hello World", NULL, NULL);	// @AIE - the screen resolution has changed from the previous tutorial?
	
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

	// ## Triangle Data
	const float vertexPositions[] =
	{
		1024 / 2.0, 720 / 2.0 + 10.0f, 0.0f, 1.0f,
		1024 / 2.0 - 5.0f, 720 / 2.0 - 10.0f, 0.0f, 1.0f,	//@AIE - typo on this line! there was a duplicate "f"!
		1024 / 2.0 + 5.0f, 720 / 2.0 - 10.0f, 0.0f, 1.0f,
	};

	const float vertexColours[] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

	// ## Triangle Shaders
	GLuint uiProgramFlat = CreateProgram("resources/shaders/VertexShader.glsl", "resources/shaders/FlatFragmentShader.glsl");

	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");	// get handle to MVP uniform in shader

	float * orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);


	// loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Draw code goes here

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// color of empty pixel
		glClear(GL_COLOR_BUFFER_BIT);			// clear using the specified method

		//enable shaders
		glUseProgram(uiProgramFlat);

		//send our orthographic projection info to the shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//enable the vertex array state, since we're sending in an array of vertices
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		//specify where our vertex array is, how many components each vertex has, 
		//the data type of each component and whether the data is normalised or not
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vertexPositions);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vertexColours);

		//draw to the screen
		glDrawArrays(GL_TRIANGLES, 0, 3);

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