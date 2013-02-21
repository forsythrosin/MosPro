#include "glEngine2D.h"

glEngine2D::glEngine2D(glm::vec3 camera){
	programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	modelID = glGetUniformLocation(programID, "MM");
	viewID = glGetUniformLocation(programID, "VM");
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
		buffers.push_back(new BufferObject(shapeList[i]));
	}
}


void glEngine2D::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	for(unsigned int i = 0; i < buffers.size(); i++){

		glUseProgram(programID);
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &buffers[i]->getShape()->getModel()[0][0]);
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getVertexBuffer());
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);


		glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->getColorBuffer());
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		glDrawArrays(GL_TRIANGLE_FAN, 0, buffers.at(i)->getShape()->getLocalVertices().size());



	}
	for(unsigned int i = 0; i < temporaryLines.size(); i++){
		if(temporaryLines[i]->frameStep()){
			temporaryLines.erase(temporaryLines.begin()+i);
			continue;
		}
		glm::mat4 model = glm::mat4(1.0f);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &temporaryLines[i]->getShape()->getModel()[0][0]);
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, temporaryLines.at(i)->getVertexBuffer());
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);


		glBindBuffer(GL_ARRAY_BUFFER, temporaryLines.at(i)->getColorBuffer());
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		glDrawArrays(GL_TRIANGLE_FAN, 0, temporaryLines[i]->getShape()->getLocalVertices().size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	glfwSwapBuffers();
}

void glEngine2D::deleteBuffers(){
	buffers.clear();
}