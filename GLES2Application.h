#pragma once

#include <epoxy/gl.h>
#include <epoxy/egl.h>

typedef struct GLFWwindow GLFWwindow;

namespace LearningGLES2 {

class GLES2Application {
public:
    GLES2Application();
    virtual ~GLES2Application() = default;

    virtual const char* applicationName() = 0;

    virtual const char* vertexShaderSource() = 0;
    virtual const char* fragmentShaderSource() = 0;

    virtual void initVertexAttribLocations() = 0;

    virtual void draw() = 0;

    int run();

    void setIsResizable(bool isResizable) { m_isResizable = isResizable; }

protected:
    bool m_isResizable : 1;

    GLsizei m_width { 1280 };
    GLsizei m_height { 720 };

    GLFWwindow* m_window { nullptr };

    GLuint m_vertexShader { 0 };
    GLuint m_fragmentShader { 0 };
    GLuint m_programObject { 0 };

private:
    bool initGLFW();
    bool initGL();

    GLuint loadShader(GLenum type, const char* src);
};

} // namespace LearningGLES2
