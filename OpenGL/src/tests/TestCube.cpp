#include "tests/TestCube.h"

#include "Debug.h"
#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace test
{
    TestCube::TestCube() :
        m_ClearColor{ 0.8f, 0.3f, 0.2f, 1.0f },
        m_Positions{
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,//A 1
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, //B 2
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  //C 3
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, //D 4
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, //E 5
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  //F 6
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f,   //G 7
            -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  //H 8
            -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  //I 9
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, //J 10
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,//K 11
             0.5f,  0.5f,  0.5f, 1.0f, 0.0f,   //L 12
             0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //M 13
             0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  //N 14
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, //O 15
            -0.5f,  0.5f,  0.5f, 0.0f, 0.0f  //P 16
    },
        m_Indices{
             0,  1,  2,  2,  3,  0,
             4,  5,  6,  6,  7,  4,
             8,  9, 10, 10,  4,  8,
            11,  2, 12, 12, 13, 11,
            10, 14,  5,  5,  4, 10,
             3,  2,  11, 11, 15, 3
    },
        m_va(),
        m_ib(m_Indices, 36),
        m_vb(m_Positions, 5 * 16 * sizeof(float)),
        m_layout(),
        m_shader("res/shaders/Complex.shader"),
        m_texture("res/textures/phone.png"),
        m_renderer(),
        m_proj(glm::perspective(glm::radians(45.0f),960.0f/540.0f, 0.1f,100.0f))
        //m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
    {
        m_layout.AddFloat(3);
        m_layout.AddFloat(2);
        m_va.AddBuffer(m_vb, m_layout);

        m_texture.Bind();
        m_shader.SetUniform1i("u_Texture", 0);
        cubePositions = {
            glm::vec3(2.0f, 2.0f, -10.0f),
            glm::vec3(0.0f, 0.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
        };
    }

    TestCube::~TestCube()
    {
        m_va.Unbind();
        m_shader.Unbind();
    }

    void TestCube::OnUpdate(float deltaTime)
    {
    }

    void TestCube::OnRender()
    {
        m_renderer.Clear();
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        {
            const float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            glm::mat4 m_view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0));

            int i = 0;
            for (auto& cubePosition : cubePositions)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePosition);
                float angle = 20.0f * i;
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
                glm::mat4 mvp = m_proj * m_view * model;
                m_shader.Bind();
                m_shader.SetUniformMat4f("u_MVP", mvp);
                m_renderer.Draw(m_va, m_ib, m_shader);
                i++;
            }
        }

    }

    void TestCube::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
};
