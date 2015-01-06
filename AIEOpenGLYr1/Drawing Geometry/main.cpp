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

	Vertex * myShape = new Vertex[3];
	
	// define XY position of each shape
	myShape[0].fPositions[0] = 1024 / 2.0;
	myShape[0].fPositions[1] = 720 / 2.0 + 10.0f;
	myShape[1].fPositions[0] = 1024 / 2.0 - 5.0f;
	myShape[1].fPositions[1] = 720 / 2.0 - 10.0f;
	myShape[2].fPositions[0] = 1024 / 2.0 + 5.0f;
	myShape[2].fPositions[1] = 720 / 2.0 - 10.0f;

	// Populate each shape with colros
	for (int i = 0; i < 3; i++)
	{
		myShape[i].fPositions[2] = 0.0f;
		myShape[i].fPositions[3] = 1.0f;
		myShape[i].fColours[0] = 0.0f;
		myShape[i].fColours[1] = 0.0f;
		myShape[i].fColours[2] = 1.0f;
		myShape[i].fColours[3] = 1.0f;
	}

	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);	// Generate VBO
	if (uiVBO != NULL)			// Populate VBO
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 3, NULL, GL_STATIC_DRAW);	//allocate space for vertices on the graphics card		
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);	//get pointer to allocated space on the graphics card
		memcpy(vBuffer, myShape, sizeof(Vertex)* 3);	//copy data to graphics card
		glUnmapBuffer(GL_ARRAY_BUFFER);	//unmap and unbind buffer

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Draw code goes here

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// color of empty pixel
		glClear(GL_COLOR_BUFFER_BIT);			// clear using the specified method

		
		//enable shaders
		glUseProgram(uiProgramFlat);	// bind program	//@AIE: why did the variable name change?

		//send our orthographic projection info to the shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//enable the vertex array state, since we're sending in an array of vertices
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);	// Bind VBO

		/*Since the data is in the same array, we need to specify the gap between
		vertices (A whole Vertex structure instance) and the offset of the data
		from the beginning of the structure instance. The positions are at the
		start, so their offset is 0. But the colours are after the positions, so
		they are offset by the size of the position data */
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

		//draw to the screen
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		

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

	glDeleteBuffers(1, &uiVBO);	//@AIE: please clean up VBO

	glfwTerminate();
	return 0;
}