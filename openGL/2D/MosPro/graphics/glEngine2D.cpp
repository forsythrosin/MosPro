#include "glEngine2D.h"

glEngine2D::glEngine2D(glm::vec3 camera){
	programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	modelID = glGetUniformLocation(programID, "MM");
	viewID = glGetUniformLocation(programID, "VM");
	setCamera(camera);
}

void glEngine2D::add(Shape2D* s){
	shapeList.push_back(s);
	s->engine = this;
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

void glEngine2D::drawLine(glm::vec2 start, glm::vec2 end, glm::vec3 color){
	GLfloat glBuffer[6] = {start.x, start.y, 0, end.x, end.y, 0};
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer), glBuffer, GL_STATIC_DRAW);
	
	GLfloat colorL[6] = {color.r, color.g, color.b, color.r, color.g, color.b};
	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorL), colorL, GL_STATIC_DRAW);
	temporaryLines.push_back(new BufferObject(colorBuffer, vertexBuffer));
}

void glEngine2D::drawVector(glm::vec2 orig, glm::vec2 direc, glm::vec3 color){
	drawLine(orig, orig+direc, color);
}

void glEngine2D::bindBuffers(){
	for(unsigned int i = 0; i < shapeList.size();i++){
		GLfloat* glBuffer = new GLfloat[shapeList[i]->getLocalVertices().size()*3];
		for(unsigned int j = 0; j < shapeList[i]->getLocalVertices().size(); j++){
		glBuffer[j*3+0] = shapeList[i]->getLocalVertices()[j].x;
		glBuffer[j*3+1] = shapeList[i]->getLocalVertices()[j].y;
		glBuffer[j*3+2] = 0;
	}
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*shapeList[i]->getLocalVertices().size()*3, glBuffer, GL_STATIC_DRAW);
		delete[] glBuffer;


		GLuint colorBuffer;
		GLfloat* colorL = new GLfloat[shapeList[i]->getLocalVertices().size()*3];
		for(unsigned int j = 0; j < shapeList[i]->getLocalVertices().size(); j++){
			colorL[j*3+0] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].x;
			colorL[j*3+1] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].y;
			colorL[j*3+2] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].z;
		}
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*shapeList[i]->getLocalVertices().size()*3, colorL, GL_STATIC_DRAW);
		buffers.push_back(new BufferObject(colorBuffer, vertexBuffer));
		delete[] colorL;
}
}


void glEngine2D::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
	for(unsigned int i = 0; i < buffers.size(); i++){

		glUseProgram(programID);

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &shapeList[i]->getModel()[0][0]);
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
		glDrawArrays(GL_TRIANGLE_FAN, 0, shapeList.at(i)->getLocalVertices().size());


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	for(int i = 0; i < temporaryLines.size(); i++){
		glm::mat4 model = glm::mat4(1.0f);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
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
	}
	glfwSwapBuffers();
}

void glEngine2D::deleteBuffers(){
	buffers.clear();
}