#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "geometry2D.h"
#include "material2D.h"

class Shape2D{
public:
	Shape2D(Geometry2D* g = new Geometry2D, Material2D* m = new Material2D):geometry(g), material(m){};
	~Shape2D();
	void setAttribs(glm::vec2 pos, double theta, glm::vec2 pivot = glm::vec2(0));
	void setGeo(Geometry2D geo); //Not implemented
	void setMat(Material2D mat); //Not implemented
	std::vector<glm::vec2> getLocalVertices();
	std::vector<glm::vec2> getGlobalVertices();
	Material2D* getMaterial();
	Geometry2D* getGeometry();
	glm::mat4 getModel();
	glm::vec2 getPointInGlobalCoordinates(glm::vec2 localCoordinates);
private:
	Geometry2D* geometry;
	Material2D* material;
	glm::mat4 modelMatrix;
	std::vector<glm::vec2> globalVertices;
};
