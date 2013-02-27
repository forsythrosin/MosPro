#pragma once
//#ifndef __COLLISIONDETECTOR2D__
//#define __COLLISIONDETECTOR2D__
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "../glmIO.h"
#include "collision2D.h"
//#include "rigidBody2D.h"
#include "minkowskiPoint2D.h"
#include "edge.h"
#include <iostream>
#include <limits>
#include "collision2D.h"
#include "bspNode2D.h"




typedef std::vector<MinkowskiPoint2D> simplex2D;
class RigidBody2D;
class Collision2D;
class BSPNode2D;

class CollisionDetector2D
{
	public:
		CollisionDetector2D(void);
		~CollisionDetector2D(void);
		std::vector<Collision2D> getCollisions(std::vector<RigidBody2D*> &bodies);
		std::vector<Collision2D> getCollisions(BSPNode2D *bsp);
	private:
		bool gjk(RigidBody2D* a, RigidBody2D* b, simplex2D &s);
		Collision2D epa(RigidBody2D* a, RigidBody2D* b, simplex2D &s);
		bool containsOrigin(simplex2D &s, glm::vec2 &d);
		Edge findClosestEdge(simplex2D &s);
		const static double tolerance;
};

//#endif


