#include "BSPNode2D.h"

BSPNode2D::BSPNode2D(BSPNode2D *parent, BSPLocation2D location, double granularity) {
	assert(parent);

	this->location = location;
	this->parent = parent;
	this->bodies = std::set<RigidBody2D*>();
	

	this->size = parent->size * 0.5f;
	glm::vec2 parentCenter = parent->globalCenter;

	switch (location) {
		case rightUpper:
			this->globalCenter = glm::vec2(parentCenter.x + size.x/2, parentCenter.y + size.y/2);
			break;
		case leftUpper: 
			this->globalCenter = glm::vec2(parentCenter.x - size.x/2, parentCenter.y + size.y/2);
			break;
		case leftLower: 
			this->globalCenter = glm::vec2(parentCenter.x - size.x/2, parentCenter.y - size.y/2);
			break;
		case rightLower: 
			this->globalCenter = glm::vec2(parentCenter.x + size.x/2, parentCenter.y - size.y/2);
			break;
	}

	
	if (size.x > granularity || size.y > granularity) {
		q1 = new BSPNode2D(this, BSPLocation2D::rightUpper, granularity);
		q2 = new BSPNode2D(this, BSPLocation2D::leftUpper, granularity);
		q3 = new BSPNode2D(this, BSPLocation2D::leftLower, granularity);
		q4 = new BSPNode2D(this, BSPLocation2D::rightLower, granularity);
	} else {
		q1 = NULL;
		q2 = NULL;
		q3 = NULL;
		q4 = NULL;
	}
}

BSPNode2D::BSPNode2D(glm::vec2 size, double granularity) {
	this->location = BSPLocation2D::root;
	this->size = size;
	this->parent = NULL;
	this->bodies = std::set<RigidBody2D*>();

	if (size.x > granularity || size.y > granularity) {
		q1 = new BSPNode2D(this, BSPLocation2D::rightUpper, granularity);
		q2 = new BSPNode2D(this, BSPLocation2D::leftUpper, granularity);
		q3 = new BSPNode2D(this, BSPLocation2D::leftLower, granularity);
		q4 = new BSPNode2D(this, BSPLocation2D::rightLower, granularity);
	} else {
		q1 = NULL;
		q2 = NULL;
		q3 = NULL;
		q4 = NULL;
	}
}

void BSPNode2D::updatePosition(RigidBody2D *rb) {
	if (shouldContain(rb)) {
		if (!contains(rb)) {
			insert(rb);
		}
		updateChildren(rb);
	} else {
		if (contains(rb)) {
			remove(rb);
			updateChildren(rb);
		}
	}
}	

void BSPNode2D::updateChildren(RigidBody2D *rb) {
	if (hasChildren()) {
		q1->updatePosition(rb);
		q2->updatePosition(rb);
		q3->updatePosition(rb);
		q4->updatePosition(rb);
	}
}

std::set<PotentialCollision2D> BSPNode2D::getPotentialCollisions() {
	std::set<PotentialCollision2D> pc;
	
	if (bodies.size() > 1) {
		if (hasChildren()) {
			std::set<PotentialCollision2D> pc1, pc2, pc3, pc4;

			pc1 = q1->getPotentialCollisions();
			pc2 = q2->getPotentialCollisions();
			pc3 = q3->getPotentialCollisions();
			pc4 = q4->getPotentialCollisions();

			pc.insert(pc1.begin(), pc1.end());
			pc.insert(pc2.begin(), pc2.end());
			pc.insert(pc3.begin(), pc3.end());
			pc.insert(pc4.begin(), pc4.end());
		} else {
			std::set<RigidBody2D*>::iterator i, j;
			for (i = bodies.begin(); i != bodies.end(); i++) {
				j = i;
				for (j++; j != bodies.end(); j++) {
					
					RigidBody2D *a = *i;
					RigidBody2D *b = *j;

					PotentialCollision2D pair(a, b);
					//std::cout << "potential collision" << a << " and " << b << std::endl;
					a->getEngine()->getDebug()->debugBox(getBox());
					pc.insert(pair);
				}
			}
		}
	}
	return pc;
}


Box2D BSPNode2D::getBox() {
	glm::vec2 halfSize = size * 0.5f;
	Box2D b = Box2D(-halfSize.x, -halfSize.y, halfSize.x, halfSize.y) + globalCenter;
	return b;
}

bool BSPNode2D::shouldContain(RigidBody2D *rb) {
	return getBox().intersects(rb->getBoundingBox());
}

bool BSPNode2D::contains(RigidBody2D *rb) {
	return bodies.find(rb) != bodies.end();
}


bool BSPNode2D::hasChildren() {
	return !!q1;
}

void BSPNode2D::insert(RigidBody2D *rb) {
	bodies.insert(rb);
}

void BSPNode2D::remove(RigidBody2D *rb) {
	std::set<RigidBody2D*>::iterator i = bodies.find(rb);
	if (i != bodies.end()) {
		bodies.erase(i);
	}
}

std::string BSPNode2D::getIdentifier() const {
	std::stringstream s;
	if (parent) {
		s << parent->getIdentifier();
	}
	switch (location) {
		case root:
			s << "0";
			break;
		case rightUpper:
			s << "1";
			break;
		case leftUpper:
			s << "2";
			break;
		case leftLower:
			s << "3";
			break;
		case rightLower:
			s << "4";
			break;
	}
	return s.str();
}

std::ostream &operator<< (std::ostream &out, const BSPNode2D& b) {
	return out << "BSPNode2D: " << b.getIdentifier();
}

// Todo: create destructor

