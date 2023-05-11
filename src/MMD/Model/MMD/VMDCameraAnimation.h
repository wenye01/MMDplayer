#pragma once

// 文件基于博客 https://blog.csdn.net/haseetxwd/article/details/82821533
//             https://blog.csdn.net/weixin_39797393/article/details/110736866

#include "MMDCamera.h"
#include "VMDAnimation.h"

#include <cstdint>
#include <memory>

namespace mmd
{
    struct VMDCameraAnimationKey
    {
        int32_t        m_time;
        glm::vec3    m_interest;
        glm::vec3    m_rotate;
        float        m_distance;
        float        m_fov;

        VMDBezier    m_ixBezier;
        VMDBezier    m_iyBezier;
        VMDBezier    m_izBezier;
        VMDBezier    m_rotateBezier;
        VMDBezier    m_distanceBezier;
        VMDBezier    m_fovBezier;
    };

    class VMDCameraController
    {
    public:
        using KeyType = VMDCameraAnimationKey;

        VMDCameraController();

        void Evaluate(float t);
        const MMDCamera& GetCamera() { return m_camera; }

        void AddKey(const KeyType& key)
        {
            m_keys.push_back(key);
        }
        void SortKeys();

    private:
        std::vector<VMDCameraAnimationKey>    m_keys;
        MMDCamera                            m_camera;
        size_t                                m_startKeyIndex;
    };

    class VMDCameraAnimation
    {
    public:
        VMDCameraAnimation();

        bool Create(const VMDFile& vmd);
        void Destroy();

        void Evaluate(float t);

        const MMDCamera& GetCamera() const { return m_camera; }

    private:
        using CameraControllerPtr = std::unique_ptr<VMDCameraController>;

        CameraControllerPtr    m_cameraController;

        MMDCamera    m_camera;
    };

}