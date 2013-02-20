#include "material2D.h"
Material2D::Material2D(){
	colors.push_back(
		glm::vec3(
			(double)rand()/RAND_MAX,
			(double)rand()/RAND_MAX,
			(double)rand()/RAND_MAX
		)
	);
}
Material2D::Material2D(glm::vec3 color){
	colors.push_back(color);
}

std::vector<glm::vec3> Material2D::getColors(){
	return colors;
}

int Material2D::getNumColors(){
	return colors.size();
}