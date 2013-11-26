#include "minkowskiPoint2D.h"
#include "../graphics/shape2D.h"
#include "../glmIO.h"

MinkowskiPoint2D::MinkowskiPoint2D(Shape2D* s1, Shape2D* s2, glm::vec2 d, bool debug){
	this->s1 = s1;
	this->s2 = s2;
	this->p1 = getFarthestPointInDirection(s1, d);
	this->p2 = getFarthestPointInDirection(s2, -d);
	this->p = this->p1 - this->p2;
	if(debug){
          /*		std::cout << "p1: " << this->p1 << std::endl;
		std::cout << "p2: " << this->p2 << std::endl;
		std::cout << "p3: " << this->p << std::endl;*/
	}
}

glm::vec2 MinkowskiPoint2D::getFarthestPointInDirection(Shape2D* s1, glm::vec2 d){
	std::vector<glm::vec2> vert = s1->getGlobalVertices();
	double dist = glm::dot(vert[0], d);
	int index = 0;
	for(unsigned int i = 1; i < vert.size(); i++){
		double curr = glm::dot(vert[i], d);
		//std::cout << "vert[" << i << "] = "<< vert[i] << std::endl;
		if (curr > dist){
			dist = curr;
			index = i;
		}
	}
	//std::cout << "Index: " << index << " Which is the vector " << vert[index] << std::endl;
	return vert[index];
}

glm::vec2 MinkowskiPoint2D::getP(){
	return p;
}

glm::vec2 MinkowskiPoint2D::getP1(){
	return p1;
}

glm::vec2 MinkowskiPoint2D::getP2(){
	return p2;
}
