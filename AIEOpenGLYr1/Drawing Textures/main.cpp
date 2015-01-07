//////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Author: Terry Nguyen
// Date: 01/06/2015
// Brief: Program main entrypoint
//
//////////////////////////////////////////////////////////////////////////

#include <time.h>		// time

#include <GL\glew.h>	// GLEW
#include <GL\wglew.h>	// this isn't actually needed yet

#include <GLFW\glfw3.h>	// GLFW

#include <Utilities.h>	// CreateProgram...

void stampStar(Vertex * starVertex)
{

}

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

	// ## Triangle Shaders
	GLuint uiProgramFlat = CreateProgram("resources/shaders/VertexShader.glsl", "resources/shaders/FlatFragmentShader.glsl");
	GLuint uiProgramTextured = CreateProgram("resources/shaders/VertexShader.glsl", "resources/shaders/TexturedFragmentShader.glsl");

	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");	// get handle to MVP uniform in shader

	float * orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);


	// ## DEFINE TRIANGLE DATA
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

	GLuint uiIBO;
	glGenBuffers(1, &uiIBO);

	if (uiIBO != NULL)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 3; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int width = 50, height = 50, bpp = 4;
	GLuint uiTextureId = loadTexture("resources/textures/aie-logo.jpg", width, height, bpp);

	// ## DEFINE STAR DATA
	GLuint uiStarProg = CreateProgram("resources/shaders/VertexPoint.glsl", "resources/shaders/FragmentPoint.glsl");

	Vertex * myStarVert = new Vertex;
	myStarVert->fPositions[2] = 0.0f;
	myStarVert->fPositions[3] = 1.0f;
	myStarVert->fColours[0] = 1.0f;
	myStarVert->fColours[1] = 1.0f;
	myStarVert->fColours[2] = 1.0f;
	myStarVert->fColours[3] = 1.0f;

	float myStarPos[40];

	srand(time(NULL));
	for (int i = 0; i < 40; i+=2)
	{
		myStarPos[i] = rand() % 1024;
	}
	for (int i = 1; i < 40; i+= 2)
	{
		myStarPos[i] = rand() % 720;
	}

	GLuint uiStarVBO;
	glGenBuffers(1, &uiStarVBO);

	
	// ## MAIN GAME LOOP

	// loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Draw code goes here

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// color of empty pixel
		glClear(GL_COLOR_BUFFER_BIT);			// clear using the specified method

		// Star Drawing
		{
			for (int i = 0; i < 40; i += 2)
			{
				if (uiStarVBO != NULL)
				{
					myStarVert->fPositions[0] = myStarPos[i];
					myStarVert->fPositions[1] = myStarPos[i + 1];

					//bind VBO
					glBindBuffer(GL_ARRAY_BUFFER, uiStarVBO);

					glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), NULL, GL_STATIC_DRAW);	//allocate space for vertices on the graphics card		
					GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);	//get pointer to allocated space on the graphics card
					memcpy(vBuffer, myStarVert, sizeof(Vertex));	//copy data to graphics card
					glUnmapBuffer(GL_ARRAY_BUFFER);	//unmap and unbind buffer

					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				//enable shaders
				glUseProgram(uiStarProg);	// bind program	//@AIE: why did the variable name change?

				//send our orthographic projection info to the shader
				glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

				//enable the vertex array state, since we're sending in an array of vertices
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, uiStarVBO);	// Bind VBO

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

				//draw to the screen
				glDrawArrays(GL_POINTS, 0, 1);
			}
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glUseProgram(0);
		}

		// Triangle Drawing
		{
			//enable shaders
			glUseProgram(uiProgramTextured);	// bind program	//@AIE: why did the variable name change?

			//send our orthographic projection info to the shader
			glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);	// Bind VBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO); // Bind IBO

			//enable the vertex array state, since we're sending in an array of vertices
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			// bind texture
			glBindTexture(GL_TEXTURE_2D, uiTextureId);
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));
			//now we have UVs to worry about, we need to send that info to the graphics card too
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));

			/*Since the data is in the same array, we need to specify the gap between
			vertices (A whole Vertex structure instance) and the offset of the data
			from the beginning of the structure instance. The positions are at the
			start, so their offset is 0. But the colours are after the positions, so
			they are offset by the size of the position data */
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

			//draw to the screen
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			glUseProgram(0);
		}

		// ## Player Movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 3; i++)
			{
				myShape[i].fPositions[1] += 1.f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, myShape, sizeof(Vertex)* 3);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 3; i++)
			{
				myShape[i].fPositions[1] -= 1.f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, myShape, sizeof(Vertex)* 3);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 3; i++)
			{
				myShape[i].fPositions[0] -= 1.f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, myShape, sizeof(Vertex)* 3);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 3; i++)
			{
				myShape[i].fPositions[0] += 1.f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, myShape, sizeof(Vertex)* 3);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

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
	glDeleteBuffers(1, &uiIBO); 
	delete myShape;
	

	glfwTerminate();
	return 0;
}