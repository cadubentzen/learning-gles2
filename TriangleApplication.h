#pragma once

#include "GLES2Application.h"

namespace LearningGLES2 {

class TriangleApplication final : public GLES2Application {
public:
    TriangleApplication() = default;
    ~TriangleApplication() = default;

    const char* applicationName() final { return "Triangle Application"; };

    const char* vertexShaderSource() final;
    const char* fragmentShaderSource() final;

    void initVertexAttribLocations() final;

    void draw() final;

private:
    GLint m_vPosition;
    GLint m_vColor;
};

} // namespace LearningGLES2
