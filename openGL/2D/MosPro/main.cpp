
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "physics/physicsEngine2D.h"
#include "physics/rigidBody2D.h"
#include "graphics/glEngine2D.h"


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
	glfwEnable( GLFW_STICKY_KEYS );
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	Shape2D s1;
	Shape2D s2;

	glm::vec2 p(0, 0);
	glm::vec2 v(0, 0);

	RigidBody2D r1(&s1, p, v, 0.0, 0.0);

	s1.setAttribs(glm::vec2(0), 0, 0.1);

	glEngine2D ge;
	ge.add(s1);
	ge.add(s2);
	ge.bindBuffers();

	PhysicsEngine pe();

	double i = 0;

	do{
		i+=0.01;
		pe.step();
		//GE.get(0)->setAttribs(glm::vec2(cos(i),sin(i)), 0, 0.1);
		//GE.get(1)->setAttribs(glm::vec2(-cos(i),sin(i)), 0, 0.1);
		ge.render();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	ge.deleteBuffers();
	glfwTerminate();

	return 0;
}