#include "shape.h"
const double PI = 3.1415926;

Shape::Shape(){
	this->position = glm::vec2(0,0);
	this->theta = 0;
	this->v =  glm::vec2(0,0);
	this->w = 0;
	std::vector<glm::vec2> shape;
	shape.push_back(glm::vec2(-1,-1));
	shape.push_back(glm::vec2(1,-1));
	shape.push_back(glm::vec2(1,1));
	shape.push_back(glm::vec2(-1,1));
	this->numParam = shape.size()*3;
	this->vertexList = new GLfloat[numParam];
	for(int i = 0; i < shape.size(); i++){
		this->vertexList[3*i+0] = shape[i].x;
		this->vertexList[3*i+1] = shape[i].y;
		this->vertexList[3*i+2] = 0;
	}
	this->globalVertices = new GLfloat[numParam];
}

Shape::Shape(std::vector<glm::vec2> shape, double x, double y, double theta, glm::vec2 v, double w){
	this->position = glm::vec2(x,y);
	this->theta = theta;
	this->v = v;
	this->w = 0;
	this->numParam = shape.size()*3;
	this->vertexList = new GLfloat[numParam];
	for(int i = 0; i < shape.size(); i++){
		this->vertexList[3*i+0] = shape[i].x;
		this->vertexList[3*i+1] = shape[i].y;
		this->vertexList[3*i+2] = 0;
	}
	this->globalVertices = new GLfloat[numParam];
};
void Shape::setPos(double x, double y){
	this->position.x = x;
	this->position.y = y;
}
void Shape::setTheta(double theta){
	this->theta = theta;
}
void Shape::setV(glm::vec2 v){
	this->v = v;
}
void Shape::setW(double w){
	this->w = w;
}
void Shape::setSize(double size){
	this->size = size;
}
void Shape::update(){
	this->position.x += v.x;
	this->position.y += v.y;
	this->theta += w;
}

int Shape::getSize(){
	return sizeof(vertexList)*numParam;
}
int Shape::getNumParam(){
	return numParam;
}
int Shape::getNumVertex(){
	return numParam/3;
}
glm::mat4 Shape::getMatrix(){
	return glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(this->position.x, this->position.y, 0.0f)
		)*
		glm::scale(
			glm::mat4(1.0f),
			glm::vec3(this->size)
		)*
		glm::rotate<glm::lowp_float>(
			glm::mat4(1.0f),
			this->theta,
			glm::vec3(0.0f,0.0f,1.0f)
		);
}
GLfloat* Shape::getShape(){
	return vertexList;
};
