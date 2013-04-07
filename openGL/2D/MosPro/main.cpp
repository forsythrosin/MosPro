#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <time.h>

#include "physics/physicsEngine2D.h"
#include "physics/rigidBody2D.h"
#include "physics/movableBody2D.h"
#include "graphics/glEngine2D.h"
#include "graphics/wallGeometry2D.h"
#include "physics/collisionDetector2D.h"
#include "physics/immovableBody2D.h"
#include "physics/spring.h"
#include "lib/debugGL.h"

#include "glmIO.h"
#include "graphics/shape2D.h"
#include "graphics/geometry2D.h"
#include "graphics/circleGeometry2D.h"

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
        sprintf(titlestring, "Rigid Body Simulation (%.1f FPS)", fps);
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
	srand(time(NULL));

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

	glEngine2D ge(glm::vec3(0.1f));

	PhysicsEngine2D pe(Box2D(-10, -10, 10, 10));

	Geometry2D wall = WallGeometry2D(20,0.5);
	Shape2D *wall1 = new Shape2D(&wall);
	Shape2D *wall2 = new Shape2D(&wall);
	Shape2D *wall3 = new Shape2D(&wall);
	Shape2D *wall4 = new Shape2D(&wall);


	ImmovableBody2D* rb1 = new ImmovableBody2D(wall1,vec2(-10,0),glm::pi<double>()/2);
	ImmovableBody2D* rb2 = new ImmovableBody2D(wall2,vec2(10,0),glm::pi<double>()/2);
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

	int nBodies = 5;
	for (int i = 0; i < nBodies; ++i) {
		vector<vec2> geo;
		geo.push_back(vec2(0,0));
		geo.push_back(vec2(0.8,0));	
		geo.push_back(vec2(0.8,0.8));
		geo.push_back(vec2(0,0.8));

		Geometry2D *g = new Geometry2D(geo);
		Shape2D* s = new Shape2D(g);
		ge.add(s);
		glm::vec2 p(-8 + i*1.2, -5);
		glm::vec2 v(0);
		double w = i*0.03 - 0.1;

		MovableBody2D* rb = new MovableBody2D(s, p, 0, v, w); 
		pe.add(rb);
	}
	 
	{
		int n = 5;
		for (int i = 0; i < n; ++i) {
			int m = 5;
			for (int j = 0; j < m; ++j) {
				vector<vec2> geo;
				geo.push_back(vec2(0,0));
				geo.push_back(vec2(0.5+ 0.02*j,0));
				geo.push_back(vec2(0.8+ 0.015*i ,0.5));
				geo.push_back(vec2(0,0.7));

				Geometry2D *g = new Geometry2D(geo);
				Shape2D* s = new Shape2D(g);
				ge.add(s);
				glm::vec2 p(2 - j*0.3 + i*1.4, -3+1.5*j);
				glm::vec2 v(0);
				double w = i*0.03 - 0.1;

				MovableBody2D* rb = new MovableBody2D(s, p, 0, v, w); 
				pe.add(rb);
			}
		}
	}
	

	

	MovableBody2D* car;
	MovableBody2D* frontWheel;
	MovableBody2D* rearWheel;

	{
		vector<vec2> geo2;
		geo2.push_back(vec2(-3, 1));
		geo2.push_back(vec2(-3, 0));
		geo2.push_back(vec2(3, 0));
		geo2.push_back(vec2(2, 1));
		Geometry2D *g = new Geometry2D(geo2);
		

		Shape2D* s = new Shape2D(g);
		ge.add(s);
		car = new MovableBody2D(s, glm::vec2(0, -8), 0, glm::vec2(0), 0); 

		Geometry2D *w = new CircleGeometry2D(0.3, 20);
		Shape2D* w1 = new Shape2D(w);
		Shape2D* w2 = new Shape2D(w);
		frontWheel = new MovableBody2D(w1, glm::vec2(2, -8.5), 0, glm::vec2(0), 0); 
		rearWheel = new MovableBody2D(w2, glm::vec2(-2.5, -8.5), 0, glm::vec2(0), 0); 
	
		ge.add(w1);
		ge.add(w2);

		Spring s1(car, glm::vec2(1.0, 0), frontWheel, glm::vec2(0, 0), 0.6, 0.005, 0.005);
		Spring s2(car, glm::vec2(2.0, 0), frontWheel, glm::vec2(0, 0), 0.6, 0.005, 0.005);

		Spring s3(car, glm::vec2(-2, 0), rearWheel, glm::vec2(0, 0), 0.6, 0.005, 0.005);
		Spring s4(car, glm::vec2(-3, 0), rearWheel, glm::vec2(0, 0), 0.6, 0.005, 0.005);


		pe.add(car);
		pe.add(frontWheel);
		pe.add(rearWheel);
		pe.add(&s1);
		pe.add(&s2);
		pe.add(&s3);
		pe.add(&s4);
	}

	

	ge.bindBuffers();
	glfwSwapInterval(1);
	do{
		showFPS();
		ge.render();
		pe.step();
		//e = pe.getTotalKineticEnergy();
		/*
		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			double w = frontWheel->getAngularVelocity();
			w -= 0.06;
			frontWheel->setAngularVelocity(w);

			w = rearWheel->getAngularVelocity();
			w -= 0.06;
			rearWheel->setAngularVelocity(w);
		}

		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
			double w = frontWheel->getAngularVelocity();
			w += 0.06;
			frontWheel->setAngularVelocity(w);

			w = rearWheel->getAngularVelocity();
			w += 0.06;
			rearWheel->setAngularVelocity(w);
		}*/
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();
	glfwTerminate();
	
	return 0;
}
