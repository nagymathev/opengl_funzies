#pragma once
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "glm/gtx/transform.hpp"

namespace test
{
    class TestMultipleObjects : public Test
    {
    public:
        TestMultipleObjects();
        ~TestMultipleObjects() override;

        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer renderer) override;
        void OnImGuiRender() override;
    private:
        float positions[16] = {
            -50.0f,  -50.0f, 0.0f, 0.0f, // 0
             50.0f,  -50.0f, 1.0f, 0.0f, // 1
             50.0f,   50.0f, 1.0f, 1.0f, // 2
            -50.0f,   50.0f, 0.0f, 1.0f // 3
       };
        unsigned indicies[6] = {
            0, 1, 2,
            2, 3, 0
        };
        VertexArray va;
        VertexBuffer vb{positions, sizeof(positions)};
        VertexBufferLayout layout;
        IndexBuffer ib{indicies, 6};
        Shader shader{"res/shaders/Basic.glsl"};
        Texture texture{"res/textures/awesomeface.png"};

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        glm::vec3 translation{200, 200, 0};
        glm::vec3 translation2{400, 200, 0};
    };
}
