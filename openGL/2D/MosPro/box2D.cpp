#include "Box2D.h"
#include "glmIO.h"
class Box2D;

Box2D::Box2D()
{
	this->p0 = glm::vec2(0, 0);
	this->p1 = glm::vec2(0, 0);
}

Box2D::Box2D(glm::vec2 p0, glm::vec2 p1)
{
	this->p0 = p0;
	this->p1 = p1;
}

Box2D::Box2D(double x0, double y0, double x1, double y1)
{
	assert(x0 <= x1);
	assert(y0 <= y1);
	this->p0 = glm::vec2(x0, y0);
	this->p1 = glm::vec2(x1, y1);
}


Box2D Box2D::intersection(const Box2D &b) const {

	double left = std::max(p0.x, b.p0.x);
	double right = std::min(p1.x, b.p1.x);

	double top = std::min(p1.y, b.p1.y);
	double bottom = std::max(p0.y, b.p0.y);
	
	if (left < right && top > bottom) {
		return Box2D(left, bottom, right, top);
	} else {
		return Box2D();
	}
}

bool Box2D::intersects(const Box2D& box) const
{
	return intersection(box) != Box2D();
}

Box2D Box2D::operator+ (const glm::vec2 v) const {
	return Box2D(p0 + v, p1 + v);
}

bool Box2D::operator== (const Box2D& b) const {
	return p0 == b.p0 && p1 == b.p1;
}

bool Box2D::operator!= (const Box2D& b) const {
	return p0 != b.p0 || p1 != b.p1;
}

bool Box2D::isEmpty() const {
	return (p0.x == p1.x && p0.y == p1.y);
}

Box2D Box2D::operator+ (const Box2D b) const {

	if (isEmpty()) {
		return b;
	} else if (b.isEmpty()) {
		return *this;
	}

	double left = std::min(p0.x, b.p0.x);
	double right = std::max(p1.x, b.p1.x);

	double top = std::max(p1.y, b.p1.y);
	double bottom = std::min(p0.y, b.p0.y);
	
	return Box2D(left, bottom, right, top);
}

Box2D Box2D::operator+= (const Box2D b) {
	*this = *this + b;
	return *this + b;
}


Box2D::~Box2D(void)
{
}


std::ostream &operator<< (std::ostream &out, const Box2D& b) {
	return out << "Box2D: [" << b.p0 << ", " << b.p1 << "]";
}