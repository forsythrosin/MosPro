#pragma once
//#ifndef __BSPNODE2D__
//#define __BSPNODE2D__

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cassert>
#include <set>
#include <string>
#include <sstream>

class PotentialCollision2D;
class Box2D;

//typedef std::pair<RigidBody2D*, RigidBody2D*> PotentialCollision2D;

enum BSPLocation2D {
	rightUpper,
	leftUpper,
	leftLower,
	rightLower,
	root
};

class RigidBody2D;

class BSPNode2D {
public:
	BSPNode2D(BSPNode2D *parent, BSPLocation2D location, double granularity);
	BSPNode2D(glm::vec2 size, double granularity);
	std::set<PotentialCollision2D> BSPNode2D::getPotentialCollisions();

	void updatePosition(RigidBody2D *rb);
	double getSize();
	
	std::string getIdentifier() const;
private:
	BSPNode2D *parent;
	BSPNode2D *q1, *q2, *q3, *q4;
	BSPLocation2D location;
	glm::vec2 globalCenter;
	glm::vec2 size;
	std::set<RigidBody2D*> bodies;
	Box2D getBox();
	bool contains(RigidBody2D *rb);
	bool shouldContain(RigidBody2D *rb);
	void updateChildren(RigidBody2D *rb);
	bool hasChildren();
	
	void insert(RigidBody2D *rb);
	void remove(RigidBody2D *rb);



	
};

std::ostream &operator<< (std::ostream &out, const BSPNode2D& node);




//#endif