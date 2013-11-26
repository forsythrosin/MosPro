#pragma once

#include <set>
class RigidBody2D;


class PotentialCollision2D {
	public:
		PotentialCollision2D(RigidBody2D* a, RigidBody2D* b);
		RigidBody2D *first;
		RigidBody2D *second;
		bool operator<(const PotentialCollision2D &other) const;
};