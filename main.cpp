#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

int main() {
    glm::vec3 v = glm::vec3(1.0f, 2.0f, 3.0f);
    std::cout << "y = " << v.y << std::endl;
    return 0;
}
