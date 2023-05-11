#pragma once

// 文件基于博客 https://blog.csdn.net/haseetxwd/article/details/82821533
//             https://blog.csdn.net/weixin_39797393/article/details/110736866

#include "VMDFile.h"

#include <MMD/Base/Log.h>
#include <MMD/Base/File.h>

namespace mmd
{
    namespace
    {
        template <typename T>
        bool Read(T* val, File& file)
        {
            return file.Read(val);
        }

        bool ReadHeader(VMDFile* vmd, File& file)
        {
            Read(&vmd->m_header.m_header, file);
            Read(&vmd->m_header.m_modelName, file);

            if (vmd->m_header.m_header.ToString() != "Vocaloid Motion Data 0002" &&
                vmd->m_header.m_header.ToString() != "Vocaloid Motion Data"
                )
            {
                MMD__WARN("VMD Header error.");
                return false;
            }

            return !file.IsBad();
        }

        bool ReadMotion(VMDFile* vmd, File& file)
        {
            uint32_t motionCount = 0;
            if (!Read(&motionCount, file))
            {
                return false;
            }

            vmd->m_motions.resize(motionCount);
            for (auto& motion : vmd->m_motions)
            {
                Read(&motion.m_boneName, file);
                Read(&motion.m_frame, file);
                Read(&motion.m_translate, file);
                Read(&motion.m_quaternion, file);
                Read(&motion.m_interpolation, file);
            }

            return !file.IsBad();
        }

        bool ReadBlednShape(VMDFile* vmd, File& file)
        {
            uint32_t blendShapeCount = 0;
            if (!Read(&blendShapeCount, file))
            {
                return false;
            }

            vmd->m_morphs.resize(blendShapeCount);
            for (auto& morph : vmd->m_morphs)
            {
                Read(&morph.m_blendShapeName, file);
                Read(&morph.m_frame, file);
                Read(&morph.m_weight, file);
            }

            return !file.IsBad();
        }

        bool ReadCamera(VMDFile* vmd, File& file)
        {
            uint32_t cameraCount = 0;
            if (!Read(&cameraCount, file))
            {
                return false;
            }

            vmd->m_cameras.resize(cameraCount);
            for (auto& camera : vmd->m_cameras)
            {
                Read(&camera.m_frame, file);
                Read(&camera.m_distance, file);
                Read(&camera.m_interest, file);
                Read(&camera.m_rotate, file);
                Read(&camera.m_interpolation, file);
                Read(&camera.m_viewAngle, file);
                Read(&camera.m_isPerspective, file);
            }

            return !file.IsBad();
        }

        bool ReadLight(VMDFile* vmd, File& file)
        {
            uint32_t lightCount = 0;
            if (!Read(&lightCount, file))
            {
                return false;
            }

            vmd->m_lights.resize(lightCount);
            for (auto& light : vmd->m_lights)
            {
                Read(&light.m_frame, file);
                Read(&light.m_color, file);
                Read(&light.m_position, file);
            }

            return !file.IsBad();
        }

        bool ReadShadow(VMDFile* vmd, File& file)
        {
            uint32_t shadowCount = 0;
            if (!Read(&shadowCount, file))
            {
                return false;
            }

            vmd->m_shadows.resize(shadowCount);
            for (auto& shadow : vmd->m_shadows)
            {
                Read(&shadow.m_frame, file);
                Read(&shadow.m_shadowType, file);
                Read(&shadow.m_distance, file);
            }

            return !file.IsBad();
        }

        bool ReadIK(VMDFile* vmd, File& file)
        {
            uint32_t ikCount = 0;
            if (!Read(&ikCount, file))
            {
                return false;
            }

            vmd->m_iks.resize(ikCount);
            for (auto& ik : vmd->m_iks)
            {
                Read(&ik.m_frame, file);
                Read(&ik.m_show, file);
                uint32_t ikInfoCount = 0;
                if (!Read(&ikInfoCount, file))
                {
                    return false;
                }
                ik.m_ikInfos.resize(ikInfoCount);
                for (auto& ikInfo : ik.m_ikInfos)
                {
                    Read(&ikInfo.m_name, file);
                    Read(&ikInfo.m_enable, file);
                }
            }

            return !file.IsBad();
        }

        bool ReadVMDFile(VMDFile* vmd, File& file)
        {
            if (!ReadHeader(vmd, file))
            {
                MMD__WARN("ReadHeader Fail.");
                return false;
            }

            if (!ReadMotion(vmd, file))
            {
                MMD__WARN("ReadMotion Fail.");
                return false;
            }

            if (file.Tell() < file.GetSize())
            {
                if (!ReadBlednShape(vmd, file))
                {
                    MMD__WARN("ReadBlednShape Fail.");
                    return false;
                }
            }

            if (file.Tell() < file.GetSize())
            {
                if (!ReadCamera(vmd, file))
                {
                    MMD__WARN("ReadCamera Fail.");
                    return false;
                }
            }

            if (file.Tell() < file.GetSize())
            {
                if (!ReadLight(vmd, file))
                {
                    MMD__WARN("ReadLight Fail.");
                    return false;
                }
            }

            if (file.Tell() < file.GetSize())
            {
                if (!ReadShadow(vmd, file))
                {
                    MMD__WARN("ReadShadow Fail.");
                    return false;
                }
            }

            if (file.Tell() < file.GetSize())
            {
                if (!ReadIK(vmd, file))
                {
                    MMD__WARN("ReadIK Fail.");
                    return false;
                }
            }

            return true;
        }
    }

    bool ReadVMDFile(VMDFile * vmd, const char * filename)
    {
        File file;
        if (!file.Open(filename))
        {
            MMD__WARN("VMD File Open Fail. {}", filename);
            return false;
        }

        return ReadVMDFile(vmd, file);
    }

}
