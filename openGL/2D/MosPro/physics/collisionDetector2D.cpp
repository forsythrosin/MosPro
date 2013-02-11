#include "collisionDetector2D.h"

CollisionDetector2D::CollisionDetector2D(void){
}


CollisionDetector2D::~CollisionDetector2D(void){
}


bool CollisionDetector2D::gjk(RigidBody2D* a, RigidBody2D* b, Collision2D &c) {
	simplex2D s;
	glm::vec2 d = b->getPosition() - a->getPosition();
	d = glm::normalize(d);
	s.push_back(MinkowskiPoint2D(a->getShape(), b->getShape(), d));
	d *= -1.0;

	while(true){
		s.push_back(MinkowskiPoint2D(a->getShape(), b->getShape(), d));
		glm::vec2 p = s[s.size()-1].getP();
		if(glm::dot(p, d) < 0){
			return false;
		} else {
			if(containsOrigin(s,d)){
				return true;
			}
		}
	}
}


bool CollisionDetector2D::containsOrigin(simplex2D &s, glm::vec2 &d) {
	glm::vec2 a = s[s.size()-1].getP();
	glm::vec2 ao = -1.0f*a;

	if (s.size() == 3) {

		glm::vec2 b = s[1].getP();
		glm::vec2 c = s[0].getP();

		glm::vec2 ab = b - a;
		glm::vec2 ac = c - a;

		/*std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
		std::cout << "c: " << c << std::endl;*/


		glm::vec2 abPerp = ab*glm::dot(ac,ab) - ac*glm::dot(ab,ab);
		glm::vec2 acPerp = ac*glm::dot(ab,ac) - ab*glm::dot(ac,ac);

		if (glm::dot(abPerp,ao) > 0) {
			s.erase(s.begin());
			d = abPerp;
		} else if (glm::dot(acPerp, ao) > 0) {
			s.erase(s.begin()+1);
			d = acPerp;
		} else {
			return true;
		}
	} else {
		glm::vec2 b = s[0].getP();
		glm::vec2 ab = b - a;
		glm::vec2 abPerp = glm::vec2(-ab.y, ab.x);
		glm::mat2 m(abPerp.x*ao.x, abPerp.y*ao.x, abPerp.x*ao.y, abPerp.y*ao.y);
		d = m*abPerp;
		/*std::cout << "ab: " << ab << std::endl;
		std::cout << "b: " << b << std::endl;
		std::cout << "abPerp: " << abPerp << std::endl;
		std::cout << "d: " << d << std::endl;
		std::cout << "ao: " << ao << std::endl;*/
	}
	return false;
}


std::vector<Collision2D> CollisionDetector2D::getCollisions(std::vector<RigidBody2D*> &bodies) {
	std::vector<Collision2D> collisions;
	for(int i = 0; i < bodies.size(); i++) {
		for(int j = i + 1; j < bodies.size(); j++) {
			Collision2D c;
			//std::cout << "Test: " << j << std::endl;
			if (gjk(bodies[i], bodies[j], c)) {
				//collisions.push_back(c);			
				std::cout << "Collision detected between " << i << " and " << j << std::endl;
				std::cin.get();
			}	
		}
	}
	return collisions;
}