#ifndef MVPBUFFEROBJECT_H
#define MVPBUFFEROBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct MvpBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#endif //!MVPBUFFEROBJECT_H