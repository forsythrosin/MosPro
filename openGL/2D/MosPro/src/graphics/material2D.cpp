#include "include/graphics/material2D.h"
Material2D::Material2D(){
	color = glm::vec3(
			(double)rand()/RAND_MAX,
			(double)rand()/RAND_MAX,
			(double)rand()/RAND_MAX);
}
Material2D::Material2D(glm::vec3 color){
	this->color = color;
}

glm::vec3 Material2D::getColor(){
	return color;
}

void Material2D::setColor(glm::vec3 color){
	this->color = color;
}
