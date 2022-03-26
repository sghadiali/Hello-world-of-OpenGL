#pragma once
#include "glm/glm.hpp"

namespace test
{
    class Test
    {
        public:
            Test() {}
            virtual ~Test() {}

            virtual void OnUpdate(float deltaTime) {}
            virtual void OnRender(glm::mat4 view) {}
            virtual void OnImGuiRender() {}
    };
}
