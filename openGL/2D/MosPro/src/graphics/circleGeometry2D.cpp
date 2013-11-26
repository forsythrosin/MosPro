#include "include/graphics/circleGeometry2D.h"

std::vector<glm::vec2> CircleGeometry2D::calcCircle(double radius, int segments){
	std::vector<glm::vec2> vec;
	for(int i = 0; i < segments; i++){
		double theta = 2.0*glm::pi<double>()*i/(double)segments;
		vec.push_back(glm::vec2(radius*glm::cos(theta),radius*glm::sin(theta)));
	}
	return vec;
}
