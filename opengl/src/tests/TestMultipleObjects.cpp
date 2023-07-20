#include "TestMultipleObjects.h"

#include "imgui/imgui.h"

namespace test
{
    TestMultipleObjects::TestMultipleObjects()
    {
        va.Bind();
        vb.Bind();
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        ib.Bind();
        shader.Bind();
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
    }

    TestMultipleObjects::~TestMultipleObjects()
    {
    }

    void TestMultipleObjects::OnUpdate(float deltaTime)
    {
        Test::OnUpdate(deltaTime);
    }

    void TestMultipleObjects::OnRender(Renderer renderer)
    {
        Test::OnRender(renderer);
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }
    }

    void TestMultipleObjects::OnImGuiRender()
    {
        Test::OnImGuiRender();

        ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation2", &translation2.x, 0.0f, 960.0f);
    }
}
