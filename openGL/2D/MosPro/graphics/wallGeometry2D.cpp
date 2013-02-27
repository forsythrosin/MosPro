#include "wallGeometry2D.h"

WallGeometry2D::WallGeometry2D(double h, double w):Geometry2D(calculateWall(h, w)){}
std::vector<glm::vec2> WallGeometry2D::calculateWall(double h, double w){
	std::vector<glm::vec2> geo;
	geo.push_back(glm::vec2(-h/2,w/2));
	geo.push_back(glm::vec2(-h/2,-w/2));
	geo.push_back(glm::vec2(h/2,-w/2));
	geo.push_back(glm::vec2(h/2,w/2));
	return geo;
}