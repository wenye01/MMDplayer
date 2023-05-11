#pragma once

#include <string>

namespace mmd
{
    // 模型变换
    class MMDMorph
    {
    public:
        MMDMorph();

        void SetName(const std::string& name) { m_name = name; }
        const std::string& GetName() const { return m_name; }

        // 节点权重
        void SetWeight(float weight) { m_weight = weight; }
        float GetWeight() const { return m_weight; }
         
        void SaveBaseAnimation() { m_saveAnimWeight = m_weight; }
        void LoadBaseAnimation() { m_weight = m_saveAnimWeight; }
        void ClearBaseAnimation() { m_saveAnimWeight = 0; }
        float GetBaseAnimationWeight() const { return m_saveAnimWeight; }

    private:
        std::string    m_name;
        float        m_weight;
        float        m_saveAnimWeight;
    };
}
