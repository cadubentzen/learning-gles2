#include "GLES2Application.h"

#define GLFW_INCLUDE_ES2 1
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace LearningGLES2 {

GLES2Application::GLES2Application()
    : m_isResizable(false)
{

}

bool GLES2Application::initGLFW()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_RESIZABLE, m_isResizable ? GL_TRUE : GL_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, applicationName(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to created GLFW window\n";
        return false;
    }

    return true;
}

GLuint GLES2Application::loadShader(GLenum type, const char* src)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if (!shader)
        return 0;

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            std::string infoLog (infoLen, ' ');

            glGetShaderInfoLog(shader, infoLen, nullptr, const_cast<GLchar*>(infoLog.c_str()));
            std::cerr << "Error compiling shader:\n" << infoLog << '\n';
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

bool GLES2Application::initGL()
{
    m_vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource());
    m_fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource());

    m_programObject = glCreateProgram();
    if (!m_programObject)
        return false;

    glAttachShader(m_programObject, m_vertexShader);
    glAttachShader(m_programObject, m_fragmentShader);

    glLinkProgram(m_programObject);

    GLint linked;
    glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen = 0;

        glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            std::string infoLog (infoLen, ' ');

            glGetProgramInfoLog(m_programObject, infoLen, NULL, const_cast<GLchar*>(infoLog.c_str()));
            std::cerr << "Error linking program:\n" << infoLog << '\n';
        }

        glDeleteProgram(m_programObject);
        return false;
    }

    glClearColor(0, 0, 0, 1);

    return true;
}

int GLES2Application::run()
{
    if (!initGLFW())
        return -1;

    glfwMakeContextCurrent(m_window);
    
    if (!initGL())
        return -1;

    initVertexAttribLocations();

    while (!glfwWindowShouldClose(m_window)) {
        draw();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

} // namespace LearningGLES2