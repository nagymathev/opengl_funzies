#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

static void APIENTRY GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "[OpenGL Error] (" << message << ")" << std::endl;
}

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }

    glEnable(GL_DEBUG_OUTPUT);
    std::cout << glGetString(GL_VERSION) << std::endl;
    glDebugMessageCallback(&GLErrorCallback, 0);

    {
        const float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
             0.5f, -0.5f, 1.0f, 0.0f, // 1
             0.5f,  0.5f, 1.0f, 1.0f, // 2
            -0.5f,  0.5f, 0.0f, 1.0f // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.glsl");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.4f, 1.0f, 1.0f);

        Texture texture("res/textures/awesomeface.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0); // Value is the texture slot we passed the texture into

        // Unbind everything
        VertexArray::Unbind();
        VertexBuffer::Unbind();
        IndexBuffer::Unbind();
        Shader::Unbind();

        Renderer renderer;

        float r = 0.0f;
        float b = 0.5f;
        float increment = 0.025f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.5f, b, 1.0f);

            renderer.Draw(va, ib, shader);
            // glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

            if (r > 1.0f)
            {
                increment = -increment;
            }
            else if (r < 0.0f)
            {
                increment = -increment;
            }

            r += increment;
            b += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}