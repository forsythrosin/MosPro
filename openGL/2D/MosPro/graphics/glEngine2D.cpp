#include "glEngine2D.h"

glEngine2D::glEngine2D(glm::vec3 camera){
	programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	modelID = glGetUniformLocation(programID, "MVP");
	colorID = glGetUniformLocation(programID, "vertexColor");
	setCamera(camera);
}

void glEngine2D::add(Shape2D* s){
	shapeList.push_back(s);
}

Shape2D*& glEngine2D::get(int i){
	return shapeList[i];
}
void glEngine2D::setView(glm::mat4 view){
	viewMatrix = view;
}
void glEngine2D::setCamera(glm::vec3 camera){
	setView(glm::mat4(
		camera.x,	0.0f,		0.0f,		0.0f,
		0.0f,		camera.y,	0.0f,		0.0f,
		0.0f,		0.0f,		camera.z,	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
	));
}

void glEngine2D::drawLine(glm::vec2 start, glm::vec2 end, glm::vec3 color, double width, unsigned int frames){
//	assert(width == 1);

	std::vector<glm::vec2> geoVec;
	double length = glm::length(end-start);
	geoVec.push_back(glm::vec2(-length/2, width/2));
	geoVec.push_back(glm::vec2(-length/2, -width/2));
	geoVec.push_back(glm::vec2(length/2, -width/2));
	geoVec.push_back(glm::vec2(length/2, width/2));

	Geometry2D* geo = new Geometry2D(geoVec);
	Material2D* mat = new Material2D(color);
	glm::vec2 delta = end - start;
	double angle = std::atan2(delta.y, delta.x);

	glm::vec2 pos = (start + end) / 2.0f;


	Shape2D* s = new Shape2D(geo, mat);
	s->setAttribs(pos, angle);

	temporaryLines.push_back(new TemporaryBufferObject(s, frames));

}

void glEngine2D::drawVector(glm::vec2 orig, glm::vec2 direc, glm::vec3 color, double width, unsigned int frames){
	drawLine(orig, orig+glm::normalize(direc), color, width, frames);
}

void glEngine2D::bindBuffers(){
	for(unsigned int i = 0; i < shapeList.size();i++){
		buffers.push_front(new BufferObject(shapeList[i]));
	}
}


void glEngine2D::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::list<BufferObject*>::iterator i;

	for(i = buffers.begin(); i != buffers.end(); ++i){

		glUseProgram(programID);
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &(viewMatrix*(*i)->getShape()->getModel())[0][0]);
		glUniform3fv(colorID, 1, &((*i)->getShape()->getMaterial()->getColor())[0]);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, (*i)->getVertexBuffer());
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLE_FAN, 0, (*i)->getShape()->getLocalVertices().size());
		glDisableVertexAttribArray(0);
	}
	std::list<TemporaryBufferObject*>::iterator it;
	for(it = temporaryLines.begin(); it != temporaryLines.end(); it++){
		if((*it)->frameStep()){
			it = temporaryLines.erase(it);
			if(it == temporaryLines.end()){
				break;
			}
			continue;
		}
		glEnableVertexAttribArray(0);

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &(viewMatrix*(*it)->getShape()->getModel())[0][0]);
		glUniform3fv(colorID, 1, &((*it)->getShape()->getMaterial()->getColor())[0]);

		glBindBuffer(GL_ARRAY_BUFFER, (*it)->getVertexBuffer());
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLE_FAN, 0, (*it)->getShape()->getLocalVertices().size());
		glDisableVertexAttribArray(0);
	}
	glfwSwapBuffers();
}

void glEngine2D::deleteBuffers(){
	buffers.clear();
	temporaryLines.clear();
}