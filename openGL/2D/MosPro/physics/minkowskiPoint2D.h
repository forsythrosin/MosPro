#ifndef __MINKOWSKIPOINT2D__
#define __MINKOWSKIPOINT2D__
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "../glmIO.h"
#include "../graphics/shape2D.h"
#include <vector>
#include <iostream>

class MinkowskiPoint2D
{
public:
	MinkowskiPoint2D(Shape2D* s1, Shape2D* s2, glm::vec2 d, bool debug = false);
	~MinkowskiPoint2D(void);
	glm::vec2 getP();
private:
	glm::vec2 p1, p2, p;
	Shape2D* s1, s2;
	glm::vec2 getFarthestPointInDirection(Shape2D* s1, glm::vec2 d);
};
#endif