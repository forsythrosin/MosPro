#include "geometry2D.h"

Geometry2D::Geometry2D(){
	vecList.push_back(glm::vec2(-1,-1));
	vecList.push_back(glm::vec2(1,-1));
	vecList.push_back(glm::vec2(1,1));
	vecList.push_back(glm::vec2(-1,1));
}

std::vector<glm::vec2> Geometry2D::getVectors(){
	return vecList;
}

int Geometry2D::getNumVec(){
	return vecList.size();
}