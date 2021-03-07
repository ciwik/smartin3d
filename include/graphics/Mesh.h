#ifndef SMARTIN3D_MESH_H
#define SMARTIN3D_MESH_H

#include "precompiled.h"

namespace smartin::graphics {
    class Mesh final {
    public:
        Mesh();

        void Init(const GLfloat* vertices, const unsigned int* indices, unsigned int vertexNumber, unsigned int indexNumber);
        void Render() const;

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
