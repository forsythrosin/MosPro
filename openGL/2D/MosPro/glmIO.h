#ifndef __GLMIO__
#define __GLMIO__
#include <glm/glm.hpp>
#include <ostream>

std::ostream &operator<< (std::ostream &out, const glm::vec2 vec);

#endif