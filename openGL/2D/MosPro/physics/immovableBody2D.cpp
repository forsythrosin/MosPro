#include "immovableBody2D.h"
#include "../graphics/shape2D.h"
#include <algorithm>

ImmovableBody2D::ImmovableBody2D(Shape2D *s, glm::vec2 p, double a) : RigidBody2D(s, p, a)
{
}


ImmovableBody2D::~ImmovableBody2D(void)
{
}

const Box2D ImmovableBody2D::getBoundingBox() const{
	std::vector<glm::vec2> vec = this->shape->getGlobalVertices();
	float top = vec[0].y, right = vec[0].x,bottom = vec[0].y , left = vec[0].x;
	for(int i = 0; i < vec.size();i++){
		top = std::max(top, vec[i].y);
		right = std::max(right, vec[i].x);
		bottom = std::min(bottom, vec[i].y);		
		left = std::min(left, vec[i].x);
	}
	return Box2D(left, bottom, right,top);
}
