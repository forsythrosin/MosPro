
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "physics/physicsEngine2D.h"
#include "physics/rigidBody2D.h"
#include "graphics/glEngine2D.h"
#include "physics/collisionDetector2D.h"

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

	vector<vec2> geo;
	geo.push_back(vec2(0,0));
	geo.push_back(vec2(1,0.2));
	geo.push_back(vec2(1,1));
	geo.push_back(vec2(0,1));

	Geometry2D g1(geo);
	Geometry2D g2(geo);

	glfwSetWindowTitle( "Tutorial 04" );
	glfwEnable( GLFW_STICKY_KEYS );
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	glEngine2D ge;
	PhysicsEngine2D pe;
Shape2D* s1 = new Shape2D(&g1);
	Shape2D* s2 = new Shape2D(&g2);
	Shape2D* s3 = new Shape2D(&g2);
	Shape2D* s4 = new Shape2D(&g2);
	Shape2D* s5 = new Shape2D(&g2);
	Shape2D* s6 = new Shape2D(&g2);

	ge.add(s1);
	ge.add(s2);
	ge.add(s3);
	ge.add(s4);
	ge.add(s5);
	ge.add(s6);

	glm::vec2 p1(0.5, 0.5);
	glm::vec2 p2(2.5, 1.5);
	glm::vec2 v(0.01, 0);

	RigidBody2D* rb1 = new RigidBody2D(s1, p1, v); 
	RigidBody2D* rb2 = new RigidBody2D(s2, p2, -v); 
	RigidBody2D* rb3 = new RigidBody2D(s3, p2*-3.0f, -v); 
	RigidBody2D* rb4 = new RigidBody2D(s4, p2*3.0f, v); 
	RigidBody2D* rb5 = new RigidBody2D(s5, p2*4.0f, -v); 
	RigidBody2D* rb6 = new RigidBody2D(s6, p2*-4.0f, v); 

	pe.add(rb1);
	pe.add(rb2);
	pe.add(rb3);
	pe.add(rb4);
	pe.add(rb5);
	pe.add(rb6);
	
	ge.bindBuffers();
	
	do{
		pe.step();
		ge.render();
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();
	glfwTerminate();
	
	return 0;
}
