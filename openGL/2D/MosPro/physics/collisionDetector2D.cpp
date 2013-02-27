#include "collisionDetector2D.h"
#include "rigidBody2D.h"
#include "minkowskiPoint2D.h"
#include "collision2D.h"
#include "edge.h"
#include <set>
#include "potentialCollision2D.h"
#include "BSPNode2D.h"

const double CollisionDetector2D::tolerance = 0.0001;
CollisionDetector2D::CollisionDetector2D(void){
}


CollisionDetector2D::~CollisionDetector2D(void){
}


bool CollisionDetector2D::gjk(RigidBody2D* a, RigidBody2D* b, simplex2D &sOut) {
	simplex2D s;
	glm::vec2 d = b->getPosition() - a->getPosition();
	d = glm::normalize(d);
	s.push_back(MinkowskiPoint2D(a->getShape(), b->getShape(), d));
	d *= -1.0;
	while(true){
		MinkowskiPoint2D mp = MinkowskiPoint2D(a->getShape(), b->getShape(), d);
		s.push_back(mp);
		glm::vec2 p = s[s.size()-1].getP();
		if(glm::dot(p, d) <= 0){
			return false;
		} 
		else if(containsOrigin(s,d)){
			sOut = s;
			return true;
		}
	}
}


bool CollisionDetector2D::containsOrigin(simplex2D &s, glm::vec2 &d) {
	glm::vec2 a = s[s.size()-1].getP();
	glm::vec2 ao = a * -1.0f;

	if (s.size() == 3) {

		glm::vec2 b = s[1].getP();
		glm::vec2 c = s[0].getP();

		glm::vec2 ab = b - a;
		glm::vec2 ac = c - a;

		glm::vec2 abPerp = ab*glm::dot(ac,ab) - ac*glm::dot(ab,ab);
		glm::vec2 acPerp = ac*glm::dot(ab,ac) - ab*glm::dot(ac,ac);

		if (glm::dot(abPerp, ao) >= 0) {
			s.erase(s.begin());
			d = abPerp;
		} else if (glm::dot(acPerp, ao) >= 0) {
			s.erase(s.begin()+1);
			d = acPerp;
		} else {
			return true;
		}

	} else {
		glm::vec2 b = s[0].getP();
		glm::vec2 ab = b - a;
		glm::vec2 abPerp = glm::vec2(-ab.y, ab.x);
		d = glm::dot(abPerp, ao)*abPerp;
	}
	return false;
}

Collision2D CollisionDetector2D::epa(RigidBody2D* a, RigidBody2D* b, simplex2D &s){
	while(true){
		Edge e = findClosestEdge(s);
		MinkowskiPoint2D p(a->getShape(),b->getShape(),e.getN());
		//a->getEngine()->getDebug()->debugLine(p.getP1(),p.getP2());
		double d = glm::dot(p.getP(), glm::normalize(e.getN()));
		
		if(d - glm::length(e.getN()) < CollisionDetector2D::tolerance){

			glm::vec2 penetrationVector = e.getN();
			glm::vec2 point;
			if(glm::length((e.getMp1().getP1() - e.getMp2().getP1())) < CollisionDetector2D::tolerance){
				point = e.getMp1().getP1();

				penetrationVector *= -1;
				return Collision2D(a, b, point, penetrationVector);
			}
			else{
				point = e.getMp1().getP2();
				return Collision2D(b, a, point, penetrationVector);
			}
		}
		else{

			s.insert(s.begin()+e.getIndex(),p);

		}
	}
}

Edge CollisionDetector2D::findClosestEdge(simplex2D &s){
	double big = std::numeric_limits<int>::max();
	Edge closest = Edge(s[0],s[0] , 0, glm::vec2(big));
	for(int i = 0; i < s.size(); i++){
		int j = (i + 1) % s.size();
		glm::vec2 a = s[i].getP();
		glm::vec2 b = s[j].getP();
		glm::vec2 e = b - a;

		e = glm::normalize(e);

		//glm::mat2 m(-e.y*a.x, e.x*a.x, -e.y*a.y, e.x*a.x); 

		glm::vec2 n = glm::dot(glm::vec2(-e.y, e.x), a)*glm::vec2(-e.y,e.x);

		if(glm::length(n) < glm::length(closest.getN())){
			closest = Edge(s[i],s[j],j,n);
		}
	}
	return closest;
}



std::vector<Collision2D> CollisionDetector2D::getCollisions(std::vector<RigidBody2D*> &bodies) {
	std::vector<Collision2D> collisions;
	for(int i = 0; i < bodies.size(); i++) {
		for(int j = i + 1; j < bodies.size(); j++) {
			simplex2D s;

			RigidBody2D* a = bodies[i];
			RigidBody2D* b = bodies[j];

			if (a->getBoundingBox().intersects(b->getBoundingBox())) {
				if (gjk(bodies[i], bodies[j], s)) {
					collisions.push_back(epa(a, b, s));
				}
			}
		}
	}
	return collisions;
}


std::vector<Collision2D> CollisionDetector2D::getCollisions(BSPNode2D *rootNode) {
	std::vector<Collision2D> collisions;
	
	std::set<PotentialCollision2D> pc = rootNode->getPotentialCollisions();

	for(std::set<PotentialCollision2D>::iterator i = pc.begin(); i != pc.end(); i++) {
		RigidBody2D *a = (RigidBody2D*) i->first;
		RigidBody2D *b = (RigidBody2D*) i->second;

		simplex2D s;
		if (a->getBoundingBox().intersects(b->getBoundingBox())) {
			if (gjk(a, b, s)) {
				collisions.push_back(epa(a, b, s));
			}
		}
	}
	return collisions;
}

