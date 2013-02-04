#include "graphicsEngine.h"

graphicsEngine::graphicsEngine(){
	srand(time(0));
}

void graphicsEngine::add(Shape s){
	shapeList.push_back(s);
	color.push_back(glm::vec3((double)rand()/RAND_MAX, (double)rand()/RAND_MAX, (double)rand()/RAND_MAX));
}
void graphicsEngine::add(Shape s, double r, double g, double b){
	shapeList.push_back(s);
	color.push_back(glm::vec3(r,g,b));
}
void graphicsEngine::add(Shape s, glm::vec3 c){
	shapeList.push_back(s);
	color.push_back(c);
}
Shape* graphicsEngine::getShape(int i){
	return &(shapeList.at(i));
}
void graphicsEngine::setColor(int i, double r, double g, double b){
	color.at(i) = glm::vec3(r,g,b);
}
void graphicsEngine::setColor(int i){
	color.at(i) = (glm::vec3((double)rand()/RAND_MAX, (double)rand()/RAND_MAX, (double)rand()/RAND_MAX));
}
void graphicsEngine::bindBuffers(){
	for(unsigned int i = 0; i < shapeList.size();i++){
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, shapeList.at(i).getSize(), shapeList.at(i).getShape(), GL_STATIC_DRAW);
		vertexBuffers.push_back(vertexBuffer);

		GLuint colorBuffer;
		GLfloat* colorL = new GLfloat[shapeList.at(i).getNumParam()];
		for(int j = 0; j < shapeList.at(i).getNumVertex(); j++){
			colorL[j*3+0] = color.at(i).x;
			colorL[j*3+1] = color.at(i).y;
			colorL[j*3+2] = color.at(i).z;
		}
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, shapeList.at(i).getSize(), colorL, GL_STATIC_DRAW);
		colorBuffers.push_back(colorBuffer);
	}
}
void graphicsEngine::update(){
	for(unsigned int i = 0; i < this->shapeList.size(); i++){
		shapeList.at(i).update();
	}
}
void graphicsEngine::render(GLuint uniformID){

	for(unsigned int i = 0; i < vertexBuffers.size(); i++){

		glUniformMatrix4fv(uniformID, 1, GL_FALSE, &shapeList.at(i).getMatrix()[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers.at(i));
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffers.at(i));
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLE_FAN, 0, shapeList.at(i).getNumVertex());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}
void graphicsEngine::deleteBuffers(){
	for(unsigned int i = 0; i < shapeList.size(); i++){

	}
}