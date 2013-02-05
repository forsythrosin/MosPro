#include "shape2D.h"

void Shape2D::setAttribs(double x, double y, double theta, double scale){
	modelMatrix = glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(x, y, 0.0f)
		)*
		glm::rotate<glm::lowp_float>(
			glm::mat4(1.0f),
			theta,
			glm::vec3(0.0f,0.0f,1.0f)
		)*
		glm::scale(
			glm::mat4(1.0f),
			glm::vec3(scale)
		);
}
void Shape2D::setAttribs(glm::vec2 pos, double theta, double scale){
	this->scale = scale;
		modelMatrix = glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(pos.x, pos.y, 0.0f)
		)*
		glm::rotate<glm::lowp_float>(
			glm::mat4(1.0f),
			theta,
			glm::vec3(0.0f,0.0f,1.0f)
		)*
		glm::scale(
			glm::mat4(1.0f),
			glm::vec3(this->scale)
		);
}
std::vector<glm::vec2> Shape2D::getLocalVertices(){
	return geometry.getVectors();
}
std::vector<glm::vec2> Shape2D::getGlobalVertices(){
	std::vector<glm::vec2> outVec;
	std::vector<glm::vec2> geo = geometry.getVectors();
	for(int i = 0; i < geo.size(); i++){
		glm::vec4 v4 = modelMatrix*glm::vec4(geo[i],0,1);
		glm::vec2 v2 = glm::vec2(v4.x,v4.y);
		outVec.push_back(v2);
	}
	return outVec;
}
glm::mat4 Shape2D::getModel(){
	return modelMatrix;
}
std::vector<glm::vec3> Shape2D::getMaterial(){
	return material.getColors();
}