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
#include "include/physics/collision2D.h"
#include "include/physics/immovableBody2D.h"
#include "include/physics/spring.h"

#include "include/lib/debugGL.h"

#include "include/graphics/shape2D.h"
#include "include/graphics/geometry2D.h"
#include "include/graphics/circleGeometry2D.h"

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




void angryBirds() {
	glEngine2D ge(glm::vec3(0.1f));
	PhysicsEngine2D pe(Box2D(-10, -10, 10, 10));

	Geometry2D wall = WallGeometry2D(20,0.5);
	Geometry2D shortWall = WallGeometry2D(3,0.4);

	Material2D wallMaterial(glm::vec3(0));

	Shape2D *wall1 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall2 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall3 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall4 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall5 = new Shape2D(&shortWall, &wallMaterial);


	ImmovableBody2D* rb1 = new ImmovableBody2D(wall1,vec2(-10,0),PI/2);
	ImmovableBody2D* rb2 = new ImmovableBody2D(wall2,vec2(10,0),PI/2);
	ImmovableBody2D* rb3 = new ImmovableBody2D(wall3,vec2(0,10),0);
	ImmovableBody2D* rb4 = new ImmovableBody2D(wall4,vec2(0,-10),0);

	ImmovableBody2D* rb5 = new ImmovableBody2D(wall5,vec2(-7,-5),0.3);

	Geometry2D cGeo = CircleGeometry2D(0.2, 5);
	Shape2D *cShape = new Shape2D(&cGeo);
	
	MovableBody2D* cursor = new MovableBody2D(cShape, vec2(0), 0, vec2(0), 0);
	
	pe.add(rb1);
	pe.add(rb2);
	pe.add(rb3);
	pe.add(rb4);
	pe.add(rb5);

	ge.add(wall1);
	ge.add(wall2);
	ge.add(wall3);
	ge.add(wall4);
	ge.add(wall5);

	DebugGL debug(&ge);
	pe.setDebug(&debug);

	
	vector<Geometry2D*> geos = vector<Geometry2D*>();
	vector<Shape2D*> shapes = vector<Shape2D*>();
	vector<MovableBody2D*> bodies = vector<MovableBody2D*>();


	std::vector<glm::vec2> shooterVertices;
	shooterVertices.push_back(glm::vec2(-0.5, -2));
	shooterVertices.push_back(glm::vec2(0.5, -2));
	shooterVertices.push_back(glm::vec2(0.5, 2));
	shooterVertices.push_back(glm::vec2(-0.5, 2));

	Geometry2D shooterGeo =  Geometry2D(shooterVertices);
	Shape2D shooterShape = Shape2D(&shooterGeo, new Material2D(vec3(0.3, 0.3, 0.3)));
	MovableBody2D shooterBody = MovableBody2D(&shooterShape, vec2(-4, -8), 0.0002, vec2(0), 0);

	ge.add(&shooterShape);
	pe.add(&shooterBody);



	ge.bindBuffers();
	glfwSwapInterval(1);

	vector<RigidBody2D*> selectedObjects;

	do{

		int xPos, yPos;
		glfwGetMousePos(&xPos, &yPos);
		double worldX = xPos/1024.0*20.0 - 10;
		double worldY = - yPos/768.0*20.0 + 10;

		cursor->setPosition(vec2(worldX, worldY));
		cursor->update();
		
		for (int i = 0; i < selectedObjects.size(); i++) {
			RigidBody2D *rb = selectedObjects[i]; 
			rb->setPosition(vec2(worldX, worldY));
			rb->setVelocity(vec2(0));

			try {
				MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
				if (mb) { mb->update(); }
			} catch(std::exception e) {}

		}

		
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			CollisionDetector2D cd = CollisionDetector2D();
		
			vector<MovableBody2D*> mbs = pe.getMovableBodies();
			vector<RigidBody2D*> rbs;
			for (int i = 0; i < mbs.size(); i++) {
				mbs[i]->update();
				rbs.push_back((RigidBody2D*) mbs[i]);
			}	
			

			vector<Collision2D> collisions = cd.getCollisions(rbs, cursor);
			for (int i = 0; i < collisions.size(); i++) {
				RigidBody2D* rb = collisions[i].getOther(cursor);

				rb->setPosition(vec2(worldX, worldY));
				rb->setVelocity(vec2(0));

				try {
					MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
					if (mb) { mb->update(); }
				} catch(std::exception e) {}


				selectedObjects.push_back(rb);
			}
		} else {
			selectedObjects.clear();
		}

		showFPS();
		ge.render();
		pe.step();

		
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();

}

void fall() {
	glEngine2D ge(glm::vec3(0.1f));
	PhysicsEngine2D pe(Box2D(-10, -10, 10, 10));

	Geometry2D wall = WallGeometry2D(20,0.5);

	Material2D wallMaterial(glm::vec3(0));

	Shape2D *wall1 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall2 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall3 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall4 = new Shape2D(&wall, &wallMaterial);


	ImmovableBody2D* rb1 = new ImmovableBody2D(wall1,vec2(-10,0),glm::pi<double>()/2);
	ImmovableBody2D* rb2 = new ImmovableBody2D(wall2,vec2(10,0),glm::pi<double>()/2);
	//ImmovableBody2D* rb3 = new ImmovableBody2D(wall3,vec2(0,10),0);
	ImmovableBody2D* rb4 = new ImmovableBody2D(wall4,vec2(0,-10),0);

	Geometry2D cGeo = CircleGeometry2D(0.2, 5);
	Shape2D *cShape = new Shape2D(&cGeo);
	
	MovableBody2D* cursor = new MovableBody2D(cShape, vec2(0), 0, vec2(0), 0);
	
	pe.add(rb1);
	pe.add(rb2);
	//pe.add(rb3);
	pe.add(rb4);

	ge.add(wall1);
	ge.add(wall2);
	//ge.add(wall3);
	ge.add(wall4);

	DebugGL debug(&ge);
	pe.setDebug(&debug);

	
	vector<Geometry2D*> geos = vector<Geometry2D*>();
	vector<Shape2D*> shapes = vector<Shape2D*>();
	vector<MovableBody2D*> bodies = vector<MovableBody2D*>();

	for (int i = 0; i < 10; i++) {
		if (i > 4) {
			geos.push_back(new CircleGeometry2D(1 - i*0.06, 4 + i%3));
		} else {
			geos.push_back(new CircleGeometry2D(1 - i*0.06, 3 + i%3));
		}
		for (int j = 0; j < i; j++) {
			Shape2D *s = new Shape2D(geos[i]);
			MovableBody2D *mb = new MovableBody2D(s, vec2(j*0.5 - 5, i*0.4 + j * 0.3 + 6), 0, vec2(0), 0);
			shapes.push_back(s); 
			bodies.push_back(mb);
			ge.add(s);
			pe.add(mb);
		}
	}




	
	ge.bindBuffers();
	glfwSwapInterval(1);

	vector<RigidBody2D*> selectedObjects;

	do{

		int xPos, yPos;
		glfwGetMousePos(&xPos, &yPos);
		double worldX = xPos/1024.0*20.0 - 10;
		double worldY = - yPos/768.0*20.0 + 10;

		cursor->setPosition(vec2(worldX, worldY));
		cursor->update();
		
		for (int i = 0; i < selectedObjects.size(); i++) {
			RigidBody2D *rb = selectedObjects[i]; 
			rb->setPosition(vec2(worldX, worldY));
			rb->setVelocity(vec2(0));

			try {
				MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
				if (mb) { mb->update(); }
			} catch(std::exception e) {}

		}

		
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			CollisionDetector2D cd = CollisionDetector2D();
		
			vector<MovableBody2D*> mbs = pe.getMovableBodies();
			vector<RigidBody2D*> rbs;
			for (int i = 0; i < mbs.size(); i++) {
				mbs[i]->update();
				rbs.push_back((RigidBody2D*) mbs[i]);
			}	
			

			vector<Collision2D> collisions = cd.getCollisions(rbs, cursor);
			for (int i = 0; i < collisions.size(); i++) {
				RigidBody2D* rb = collisions[i].getOther(cursor);

				rb->setPosition(vec2(worldX, worldY));
				rb->setVelocity(vec2(0));

				try {
					MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
					if (mb) { mb->update(); }
				} catch(std::exception e) {}


				selectedObjects.push_back(rb);
			}
		} else {
			selectedObjects.clear();
		}

		showFPS();
		ge.render();
		pe.step();

		
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();


}




void cloth(void) {
	glEngine2D ge(glm::vec3(0.1f));
	PhysicsEngine2D pe(Box2D(-10, -10, 10, 10));

	Geometry2D wall = WallGeometry2D(20,0.5);

	Material2D wallMaterial(glm::vec3(0));

	Shape2D *wall1 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall2 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall3 = new Shape2D(&wall, &wallMaterial);
	Shape2D *wall4 = new Shape2D(&wall, &wallMaterial);


	ImmovableBody2D* rb1 = new ImmovableBody2D(wall1,vec2(-10,0),PI/2);
	ImmovableBody2D* rb2 = new ImmovableBody2D(wall2,vec2(10,0),PI/2);
	ImmovableBody2D* rb3 = new ImmovableBody2D(wall3,vec2(0,10),0);
	ImmovableBody2D* rb4 = new ImmovableBody2D(wall4,vec2(0,-10),0);

	Geometry2D cGeo = CircleGeometry2D(0.2, 5);
	Shape2D *cShape = new Shape2D(&cGeo);
	
	MovableBody2D* cursor = new MovableBody2D(cShape, vec2(0), 0, vec2(0), 0);
	
	//ge.add(cShape);
	//pe.add(cursor);
	

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

	//init cloth particles
	int clothWidth = 5;
	int clothHeight = 5;

	double wScaled = 20/clothWidth;
	double hScaled = 20/clothHeight;

	Geometry2D pGeo = CircleGeometry2D(0.6, 5);
	
	vector<vector<MovableBody2D*> > cloth; 

	for (int i = 0; i < clothWidth; ++i) {
		cloth.push_back(vector<MovableBody2D*>());

		for (int j = 0; j < clothHeight; ++j) {

			Shape2D* s = new Shape2D(&pGeo);
			ge.add(s);
			glm::vec2 p(-wScaled*(i - clothWidth/2), -hScaled*(j - clothHeight/2));

			MovableBody2D* rb = new MovableBody2D(s, p, 0, glm::vec2(0), 0);
			pe.add(rb);
			
			cloth[i].push_back(rb);

			if(i > 0){
				Spring *s = new Spring (cloth[i][j], glm::vec2(0), cloth[i-1][j], glm::vec2(0), wScaled, 0.001, 0.002);
				pe.add(s);
			}
			if(j > 0){
				Spring *s = new Spring (cloth[i][j], glm::vec2(0), cloth[i][j-1], glm::vec2(0), hScaled, 0.001, 0.002);
				pe.add(s);
			}
			if(i > 0 && j > 0){
				Spring *s = new Spring (cloth[i][j], glm::vec2(0), cloth[i-1][j-1], glm::vec2(0), wScaled*1.414213562373095, 0.001, 0.2);
				pe.add(s);
			}
		}
	}
	
	ge.bindBuffers();
	glfwSwapInterval(1);

	
	vector<RigidBody2D*> selectedObjects;

	do{

		int xPos, yPos;
		glfwGetMousePos(&xPos, &yPos);
		double worldX = xPos/1024.0*20.0 - 10;
		double worldY = - yPos/768.0*20.0 + 10;

		cursor->setPosition(vec2(worldX, worldY));
		cursor->update();
		
		for (int i = 0; i < selectedObjects.size(); i++) {
			RigidBody2D *rb = selectedObjects[i]; 
			rb->setPosition(vec2(worldX, worldY));
			rb->setVelocity(vec2(0));

			try {
				MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
				if (mb) { mb->update(); }
			} catch(std::exception e) {}

		}

		
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			CollisionDetector2D cd = CollisionDetector2D();
		
			vector<MovableBody2D*> mbs = pe.getMovableBodies();
			vector<RigidBody2D*> rbs;
			for (int i = 0; i < mbs.size(); i++) {
				mbs[i]->update();
				rbs.push_back((RigidBody2D*) mbs[i]);
			}	
			

			vector<Collision2D> collisions = cd.getCollisions(rbs, cursor);
			for (int i = 0; i < collisions.size(); i++) {
				RigidBody2D* rb = collisions[i].getOther(cursor);

				rb->setPosition(vec2(worldX, worldY));
				rb->setVelocity(vec2(0));

				try {
					MovableBody2D* mb = dynamic_cast<MovableBody2D*>(rb);
					if (mb) { mb->update(); }
				} catch(std::exception e) {}


				selectedObjects.push_back(rb);
			}
		} else {
			selectedObjects.clear();
		}

		showFPS();
		ge.render();
		pe.step();

		cloth[0][0]->setPosition(glm::vec2(7, 9));
		cloth[0][0]->setVelocity(glm::vec2(0));
		cloth[clothWidth-1][0]->setPosition(glm::vec2(-7, 9));
		cloth[clothWidth-1][0]->setVelocity(glm::vec2(0));
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );
		   
	ge.deleteBuffers();


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
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
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

	
	glfwEnable( GLFW_STICKY_KEYS );
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 


	//angryBirds();
	fall();

	glfwTerminate();
	
	return 0;
}
