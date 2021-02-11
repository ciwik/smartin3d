#include "graphics/Mesh.h"

smartin::graphics::Mesh::Mesh() {
    vao = 0;
    vbo = 0;
    ibo = 0;
    indexNumber = 0;
}

void smartin::graphics::Mesh::Init(GLfloat *vertices, unsigned int *indices, unsigned int vertexNumber, unsigned int _indexNumber) {
    indexNumber = _indexNumber;
    size_t indexSize = sizeof(indices[0]);
    size_t vertexSize = sizeof(vertices[0]);

    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // IBO
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * indexNumber, indices, GL_STATIC_DRAW);

    // VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexSize * vertexNumber, vertices, GL_STATIC_DRAW);

    // XYZ loading
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize * 8, 0);
    glEnableVertexAttribArray(0);

    // UV loading
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexSize * 8, (void*)(vertexSize * 3));
    glEnableVertexAttribArray(1);

    // Normals loading
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexSize * 8, (void*)(vertexSize * 5));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void smartin::graphics::Mesh::Render() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glDrawElements(GL_TRIANGLES, indexNumber, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

smartin::graphics::Mesh::~Mesh() {
    if (ibo != 0)
        glDeleteBuffers(1, &ibo);

    if (vbo != 0)
        glDeleteBuffers(1, &vbo);

    if (vao != 0)
        glDeleteBuffers(1, &vao);

    vao = 0;
    vbo = 0;
    ibo = 0;
    indexNumber = 0;
}
