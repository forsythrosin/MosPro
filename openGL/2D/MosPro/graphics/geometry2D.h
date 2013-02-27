#pragma once
//#ifndef __GEOMETRY2D__
//#define __GEOMETRY2D__
#include <glm/glm.hpp>
#include <vector>
class Geometry2D{
public:
	Geometry2D();
	Geometry2D(std::vector<glm::vec2> vec) : vecList(vec){};
	std::vector<glm::vec2> getVectors(); 
	int getNumVec();
private:
	std::vector<glm::vec2> vecList;
};
//#endif


