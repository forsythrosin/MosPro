// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <common/shader.hpp>
#include <common/shader.cpp>
#include "shape.h"
#include "graphicsEngine.h"
using namespace glm;
using namespace std;


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Tutorial 04" );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.8f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	std::vector<glm::vec2> shapeVec;
	shapeVec.push_back(glm::vec2(-1,-1));
	shapeVec.push_back(glm::vec2(1,-1));
	shapeVec.push_back(glm::vec2(1,1));
	shapeVec.push_back(glm::vec2(-2,2));

	Shape s1(shapeVec,0,0);
	s1.setSize(0.1);
	s1.setV(glm::vec2(0.0001,0));
	s1.setW(0.01);

	Shape s2(shapeVec,0,0);
	s2.setSize(0.1);
	s2.setV(glm::vec2(-0.0001,0));
	s2.setW(-0.01);

	Shape s3(shapeVec,0,0);
	s3.setSize(0.1);
	s3.setV(glm::vec2(0.0001,0.0001));
	s3.setW(-0.01);

	graphicsEngine GE;

	GE.add(s1);
	GE.add(s2);
	GE.add(s3);
	GE.bindBuffers();
	double i = 0;
	do{
		i+=0.01;
		GE.getShape(0)->setV(glm::vec2(cos(i)*0.001,0));
		GE.getShape(0)->setW(cos(i));
		GE.update();
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);
		GE.render(MatrixID);
		// Swap buffers
		glfwSwapBuffers();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Cleanup VBO and shader
	GE.deleteBuffers();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

