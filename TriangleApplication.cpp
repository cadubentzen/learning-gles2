#include "TriangleApplication.h"

namespace LearningGLES2 {

const char* TriangleApplication::vertexShaderSource()
{
    return (
        "attribute vec4 vPosition;  \n"
        "attribute vec3 vColor;     \n"
        "                           \n"
        "varying vec3 outColor;     \n"
        "                           \n"
        "void main()                \n"
        "{                          \n"
        "  gl_Position = vPosition; \n"
        "  outColor = vColor;       \n"
        "}                          \n"
    );
}

const char* TriangleApplication::fragmentShaderSource()
{
    return (
        "precision mediump float;              \n"
        "                                      \n"
        "varying vec3 outColor;                \n"
        "                                      \n"
        "void main()                           \n"
        "{                                     \n"
        "  gl_FragColor = vec4(outColor, 1.0); \n"
        "}                                     \n"
    );
}

void TriangleApplication::initVertexAttribLocations()
{
    m_vPosition = glGetAttribLocation(m_programObject, "vPosition");
    m_vColor = glGetAttribLocation(m_programObject, "vColor");
}

void TriangleApplication::draw()
{
    if (m_vPosition < 0 || m_vColor < 0)
        return;

    GLfloat vVertices[] = {   0,  0.5, 0,
                           -0.5, -0.5, 0,
                            0.5, -0.5, 0 };

    GLfloat vColors[] = { 1.0, 0.0, 0.0,
                          0.0, 1.0, 0.0,
                          0.0, 0.0, 1.0 };

    glViewport(0, 0, m_width, m_height);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_programObject);

    glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(m_vPosition);

    glVertexAttribPointer(m_vColor, 3, GL_FLOAT, GL_FALSE, 0, vColors);
    glEnableVertexAttribArray(m_vColor);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(m_window);
}

} // namespace LearningGLES2
