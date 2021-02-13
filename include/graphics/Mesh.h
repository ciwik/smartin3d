#ifndef SMARTIN3D_MESH_H
#define SMARTIN3D_MESH_H

#include <GL/glew.h>

namespace smartin::graphics {
    class Mesh {
    public:
        Mesh();

        void Init(GLfloat* vertices, unsigned int* indices, unsigned int vertexNumber, unsigned int indexNumber);
        void Render();

        ~Mesh();

    private:
        // VAO - Vertex Array Object, defines scheme of vertex data alignment
        GLuint vao;
        // VBO - Vertex Buffer Object
        GLuint vbo;
        // IBO - Index Buffer Object
        GLuint ibo;

        GLsizei indexNumber;
    };
}

#endif //SMARTIN3D_MESH_H