#include "QuadRenderer.h"

static float vertices[] = {
    // pos        // uv
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
};
static unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
};

QuadRenderer::QuadRenderer(unsigned int width, unsigned int height)
    : width{ width }, height{ height }, shader{ Shader("quad.vert", "quad.frag") },
    vertexData{ VertexData(vertices, sizeof(vertices), indices, sizeof(indices)) }
{
    // create quad to render - initialize to all yellow
    // TO-DO: Render to frame buffer
    pixels = new float[3 * width * height];
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            pixels[3 * (i * width + j)] = 1.0f;
            pixels[3 * (i * width + j) + 1] = 1.0f;
            pixels[3 * (i * width + j) + 2] = 0.0f;
        }
    }

    // create texture
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, pixels);
}

QuadRenderer::~QuadRenderer() {
    delete[] pixels;
}

void QuadRenderer::setPixel(unsigned int i, unsigned int j, float r, float g, float b) {
    pixels[3 * (i * width + j)] = r;
    pixels[3 * (i * width + j) + 1] = g;
    pixels[3 * (i * width + j) + 2] = b;
}

void QuadRenderer::render() {
    shader.use();
    shader.setUniform1i("screenTex", 0);
    glBindVertexArray(vertexData.vao);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_FLOAT, pixels);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}