#ifndef __COLLISIONDETECTOR2D__
#define __COLLISIONDETECTOR2D__

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "../glmIO.h"
#include "collision2D.h"
#include "rigidBody2D.h"
#include "minkowskiPoint2D.h"
#include <iostream>


typedef std::vector<MinkowskiPoint2D> simplex2D;
class RigidBody2D;
class CollisionDetector2D
{
	public:
		CollisionDetector2D(void);
		~CollisionDetector2D(void);
		std::vector<Collision2D> getCollisions(std::vector<RigidBody2D*> &bodies);
	private:
		bool gjk(RigidBody2D* a, RigidBody2D* b, Collision2D &c);
		bool containsOrigin(simplex2D &s, glm::vec2 &d);
};

#endif