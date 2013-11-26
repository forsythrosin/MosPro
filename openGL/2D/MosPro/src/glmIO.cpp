#include "include/glmIO.h"

std::ostream &operator<< (std::ostream &out, const glm::vec2 vec){
    out << "{" 
        << vec.x << " " << vec.y
        << "}";
    return out;
}
