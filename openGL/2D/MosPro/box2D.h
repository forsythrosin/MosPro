#ifndef __BOX2D__
#define __BOX2D__

#include <glm/glm.hpp>
#include <algorithm>
#include <cassert>
#include "glmIO.h"
#include <iostream>


class Box2D {
	public:
		Box2D::Box2D();
		Box2D::Box2D(glm::vec2 p0, glm::vec2 p1);
		Box2D::Box2D(double x0, double y0, double x1, double y1);
		~Box2D(void);
		bool intersects(const Box2D& b) const;
		Box2D intersection(const Box2D &b) const;
		bool operator== (const Box2D& b) const;
		Box2D operator+ (const glm::vec2 v) const;
		bool operator!= (const Box2D& b) const;
		
		glm::vec2 p0;
		glm::vec2 p1;
		
};

std::ostream &operator<< (std::ostream &out, const Box2D& b);



#endif