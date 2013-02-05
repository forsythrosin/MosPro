#ifndef __MATERIAL2D__
#define __MATERIAL2D__
#include <glm/glm.hpp>
#include <vector>
#include <ctime>
class Material2D{
public:
	Material2D(); //Random color
	Material2D(std::vector<glm::vec3> color):colors(color){}; //Interpolated Colors
	Material2D(glm::vec3 color); //Full color
	std::vector<glm::vec3> getColors(); //get a vector with all colors in class
	int getNumColors();
private:
	std::vector<glm::vec3> colors;
};
#endif