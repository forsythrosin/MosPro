#ifndef __CIRCLEGEOMETRY2D__
#define __CIRCLEGEOMETRY2D__
#include "geometry2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>


class CircleGeometry2D : public Geometry2D{
public:
	CircleGeometry2D(double radius, int segments):Geometry2D(calcCircle(radius,segments)){};
private:
	std::vector<glm::vec2> calcCircle(double radius, int segments);
};

#endif