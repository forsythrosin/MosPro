#pragma once
//#ifndef __MINKOWSKIPOINT2D__
//#define __MINKOWSKIPOINT2D__
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>
#include <iostream>

class Shape2D;

class MinkowskiPoint2D
{
public:
	MinkowskiPoint2D(Shape2D* s1, Shape2D* s2, glm::vec2 d = glm::vec2(0), bool debug = false);
	glm::vec2 getP();
	glm::vec2 getP1();
	glm::vec2 getP2();
private:
	glm::vec2 p1, p2, p;
	Shape2D* s1; 
	Shape2D* s2;
	glm::vec2 getFarthestPointInDirection(Shape2D* s1, glm::vec2 d);
};
//#endif
