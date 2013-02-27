#include "potentialCollision2D.h"

PotentialCollision2D::PotentialCollision2D(RigidBody2D *a, RigidBody2D *b) {
	this->first = a < b ? a : b;
	this->second = a < b ? b : a; 
}


bool PotentialCollision2D::operator<(const PotentialCollision2D &other) const {
	return this->first < other.first ? true :
		   this->first > other.first ? false :
		   this->second < other.second;
}
