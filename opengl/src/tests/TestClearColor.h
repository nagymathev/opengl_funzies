﻿#pragma once
#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer renderer) override;
        void OnImGuiRender() override;
    private:
        float m_ClearColor[4];
    };
}

