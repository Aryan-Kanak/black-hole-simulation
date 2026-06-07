#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexData.h"

const int WINDOW_WIDTH = 680;
const int WINDOW_HEIGHT = 480;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();

    // TO-DO: Refactor renderer into it's own class
    Shader shader = Shader("default.vert", "default.frag");

    // create texture to render
    // TO-DO: Render to framebuffer
    float* pixels = new float[3 * WINDOW_WIDTH * WINDOW_HEIGHT];
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++) {
            if (j < WINDOW_WIDTH / 2) {
                pixels[3 * (i * WINDOW_WIDTH + j)] = 1.0f;
                pixels[3 * (i * WINDOW_WIDTH + j) + 1] = 1.0f;
                pixels[3 * (i * WINDOW_WIDTH + j) + 2] = 0.0f;
            }
            else {
                pixels[3 * (i * WINDOW_WIDTH + j)] = 0.0f;
                pixels[3 * (i * WINDOW_WIDTH + j) + 1] = 1.0f;
                pixels[3 * (i * WINDOW_WIDTH + j) + 2] = 0.0f;
            }
        }
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, pixels);

    // create vertices for quad
    float vertices[] = {
        // pos        // uv
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexData vertexData = VertexData(vertices, sizeof(vertices), indices, sizeof(indices));
    
    shader.use();
    shader.setUniform1i("screenTex", 0);
    glBindVertexArray(vertexData.vao);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}