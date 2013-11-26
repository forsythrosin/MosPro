
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <time.h>

#include "include/physics/physicsEngine2D.h"
#include "include/physics/rigidBody2D.h"
#include "include/physics/movableBody2D.h"
#include "include/graphics/glEngine2D.h"
#include "include/graphics/wallGeometry2D.h"
#include "include/physics/collisionDetector2D.h"
#include "include/physics/immovableBody2D.h"
#include "include/lib/debugGL.h"

#include "include/graphics/shape2D.h"
#include "include/graphics/geometry2D.h"

#define PI 3.1415926535897932384626433832795 



using namespace glm;
using namespace std;


double t0 = 0.0;
int frames = 0;
char titlestring[200];



void showFPS() {

    double t, fps;
    
    // Get current time
    t = glfwGetTime();  // Get number of seconds since glfwInit()
    // Calculate and display FPS (frames per second) in title bar.
    if( (t-t0) > 1.0 || frames == 0 )
    {
        fps = (double)frames / (t-t0);
        sprintf(titlestring, "Planet system (%.1f FPS)", fps);
        glfwSetWindowTitle(titlestring);
        t0 = t;
        frames = 0;
    }
    frames ++;
}


double floatRand() {
	
	 return rand() / (double)RAND_MAX;
}

#define GLFW_OPENGL_PROFILE 0 
int main( void )
{
	srand(time(NULL));

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

        	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwOpenWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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



	//glfwSetWindowTitle( "Tutorial 04" );
	
	glfwEnable( GLFW_STICKY_KEYS );
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	glEngine2D ge(glm::vec3(0.1f));

	PhysicsEngine2D pe(Box2D(-10, -10, 10, 10));

	Geometry2D wall = WallGeometry2D(20,0.5);
	Shape2D *wall1 = new Shape2D(&wall);
	Shape2D *wall2 = new Shape2D(&wall);
	Shape2D *wall3 = new Shape2D(&wall);
	Shape2D *wall4 = new Shape2D(&wall);

	ImmovableBody2D* rb1 = new ImmovableBody2D(wall1,vec2(-10,0),PI/2);
	ImmovableBody2D* rb2 = new ImmovableBody2D(wall2,vec2(10,0),PI/2);
	ImmovableBody2D* rb3 = new ImmovableBody2D(wall3,vec2(0,10),0);
	ImmovableBody2D* rb4 = new ImmovableBody2D(wall4,vec2(0,-10),0);

	pe.add(rb1);
	pe.add(rb2);
	pe.add(rb3);
	pe.add(rb4);

	ge.add(wall1);
	ge.add(wall2);
	ge.add(wall3);
	ge.add(wall4);

	DebugGL debug(&ge);

	pe.setDebug(&debug);

	int nBodies = 40;



	for (int i = 0; i < nBodies; ++i) {

		//cout << rand() << endl;

		vector<vec2> geo;
		geo.push_back(vec2(0,0));
		geo.push_back(vec2(0.8,0));
		geo.push_back(vec2(0.8,0.8));
		geo.push_back(vec2(0,0.8));



		Geometry2D *g = new Geometry2D(geo);
		Shape2D* s = new Shape2D(g);
		ge.add(s);
		glm::vec2 p(floatRand()*20 - 10, floatRand()*20 - 10);
		glm::vec2 v(floatRand()*0.01, floatRand()*0.01);
		double w = floatRand()*0.002 - 0.1;

		//std::cout << p << v << w;


		MovableBody2D* rb = new MovableBody2D(s, p, 0, v, w); 
		pe.add(rb);
	}

	MovableBody2D* rb;

	{
		vector<vec2> geo2;
		geo2.push_back(vec2(0,0));
		geo2.push_back(vec2(1.2,0));
		geo2.push_back(vec2(2.8,0.6));
		geo2.push_back(vec2(1.2,1.2));
		geo2.push_back(vec2(0,1.2));

		Geometry2D *g = new Geometry2D(geo2);
		Shape2D* s = new Shape2D(g);
		ge.add(s);

		rb = new MovableBody2D(s, glm::vec2(0), 0, glm::vec2(0), 0); 
		pe.add(rb);
	}


	ge.bindBuffers();
	double oldE = 0, e;
	glfwSwapInterval(1);
	do{
		showFPS();
		ge.render();
		pe.step();
		e = pe.getTotalKineticEnergy();
		if(e != oldE){
			std::cout << "we have " << e << " frikikin kJoules in this sistem.\n";
			oldE = e;
		}

		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
			glm::vec2 v = rb->getVelocity();
			double angle = rb->getAngle();
			v += 0.008f*glm::vec2(glm::cos(angle), glm::sin(angle));
			rb->setVelocity(v);
		}

		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
			double w = rb->getAngularVelocity();
			w += 0.001;
			rb->setAngularVelocity(w);
		}

		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			double w = rb->getAngularVelocity();
			w -= 0.001;
			rb->setAngularVelocity(w);
		}


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();
	glfwTerminate();
	
	return 0;
}
