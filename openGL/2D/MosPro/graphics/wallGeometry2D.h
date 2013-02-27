#pragma once
#include "geometry2D.h"

class WallGeometry2D : public Geometry2D{
public:
	WallGeometry2D(double h, double w);
private:
	std::vector<glm::vec2> calculateWall(double h, double w);
};