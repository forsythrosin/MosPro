#include "shape2D.h"

void Shape2D::setAttribs(glm::vec2 pos, double theta, glm::vec2 pivot){
		modelMatrix = glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(pos.x, pos.y, 0.0f)
		)*
		glm::rotate<glm::lowp_float>(
			glm::mat4(1.0f),
			glm::degrees(theta),
			glm::vec3(0.0f,0.0f,1.0f)
		)*
		glm::translate(
			glm::mat4(1.0f),
			glm::vec3(-pivot, 0));


	globalVertices = geometry->getVectors();
	std::vector<glm::vec2> outVec(globalVertices.size());
	for(int i = 0; i < globalVertices.size(); i++){
		glm::vec4 v4 = modelMatrix*glm::vec4(globalVertices[i],0,1);
		glm::vec2 v2 = glm::vec2(v4.x,v4.y);
		globalVertices[i] = v2;
	}
}

Shape2D::~Shape2D(){
}

std::vector<glm::vec2> Shape2D::getLocalVertices(){
	return geometry->getVectors();
}


std::vector<glm::vec2> Shape2D::getGlobalVertices(){
	return globalVertices;
}


glm::mat4 Shape2D::getModel(){
	return modelMatrix;
}


Material2D* Shape2D::getMaterial(){
	return material;
}

Geometry2D* Shape2D::getGeometry(){
	return geometry;
}