#pragma once
//#ifndef __MATERIAL2D__
//#define __MATERIAL2D__
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class Material2D{
public:
	Material2D(); //Random color
	Material2D(glm::vec3 color); //Full color
	glm::vec3 getColor(); //get a vector with all colors in class
	void setColor(glm::vec3 color);
private:
	glm::vec3 color;
};
//#endif
