﻿#include "TestClearColor.h"

// #include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
    TestClearColor::TestClearColor()
        : m_ClearColor{ 0.2f, 0.3f, 0.1f, 1.0f }
    {
    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::OnUpdate(float deltaTime)
    {
        Test::OnUpdate(deltaTime);
    }

    void TestClearColor::OnRender(Renderer renderer)
    {
        Test::OnRender(renderer);
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender()
    {
        Test::OnImGuiRender();
        ImGui::ColorEdit4("Background Color", m_ClearColor);
    }
}