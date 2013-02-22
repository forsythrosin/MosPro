
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <time.h>

#include "physics/physicsEngine2D.h"
#include "physics/rigidBody2D.h"
#include "graphics/glEngine2D.h"
#include "physics/collisionDetector2D.h"
#include "lib/debugGL.h"

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


int main( void )
{
	srand(std::time(NULL));

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



	//glfwSetWindowTitle( "Tutorial 04" );
	
	glfwEnable( GLFW_STICKY_KEYS );
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	glEngine2D ge(glm::vec3(0.01f));
	PhysicsEngine2D pe(Box2D(-100, -100, 100, 100));

	DebugGL debug(&ge);

	pe.setDebug(&debug);

	int nBodies = 1000;



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
		glm::vec2 p(floatRand()*200 - 100, floatRand()*200 - 100);
		glm::vec2 v(floatRand()*0.01, floatRand()*0.01);
		double w = floatRand()*0.002 - 0.1;

		//std::cout << p << v << w;


		RigidBody2D* rb = new RigidBody2D(s, p, v, w); 
		pe.add(rb);
	}

	RigidBody2D* rb;

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

		rb = new RigidBody2D(s, glm::vec2(0), glm::vec2(0), 0, 0); 
		pe.add(rb);
	}

	ge.bindBuffers();
	double oldE = 0, e;
	do{
		showFPS();
		ge.render();
		pe.step();
		e = pe.getTotalKineticEnergy();
		if(e != oldE){
			//std::cout << "we have " << e << " frikikin kJoules in this sistem.\n";
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
