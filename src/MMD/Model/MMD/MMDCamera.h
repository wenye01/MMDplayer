#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace mmd
{
    // 摄像机
    struct MMDCamera
    {
        MMDCamera();

        glm::vec3    m_interest;
        glm::vec3    m_rotate;
        float        m_distance;
        float        m_fov;
    };

    struct MMDLookAtCamera
    {
        explicit MMDLookAtCamera(const MMDCamera& cam);

        glm::vec3    m_center;
        glm::vec3    m_eye;
        glm::vec3    m_up;
    };
} 