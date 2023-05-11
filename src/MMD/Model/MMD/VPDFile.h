#pragma once

#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace mmd
{
    struct VPDBone
    {
        std::string    m_boneName;
        glm::vec3    m_translate;
        glm::quat    m_quaternion;
    };

    struct VPDMorph
    {
        std::string    m_morphName;
        float        m_weight;
    };

    struct VPDFile
    {
        std::vector<VPDBone>    m_bones;
        std::vector<VPDMorph>    m_morphs;
    };

    bool ReadVPDFile(VPDFile* vpd, const char* filename);
}