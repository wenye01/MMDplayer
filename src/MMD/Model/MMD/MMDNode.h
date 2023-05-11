#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

namespace mmd
{
    // 节点类，或骨骼类
    class MMDNode
    {
    public:
        MMDNode();

        void AddChild(MMDNode* child);
        
        void BeginUpdateTransform();
        void EndUpdateTransform();

        void UpdateLocalTransform();
        void UpdateGlobalTransform();
        void UpdateChildTransform();

        // 数据操作函数，防止错误更改
        void SetIndex(uint32_t idx) { m_index = idx; }
        uint32_t GetIndex() const { return m_index; }

        void SetName(const std::string& name) { m_name = name; }
        const std::string& GetName() const { return m_name; }

        void EnableIK(bool enable) { m_enableIK = enable; }
        bool IsIK() const { return m_enableIK; }

        void SetTranslate(const glm::vec3& t) { m_translate = t; }
        const glm::vec3& GetTranslate() const { return m_translate; }

        void SetRotate(const glm::quat& r) { m_rotate = r; }
        const glm::quat& GetRotate() const { return m_rotate; }

        void SetScale(const glm::vec3& s) { m_scale = s; }
        const glm::vec3& GetScale() const { return m_scale; }

        void SetAnimationTranslate(const glm::vec3& t) { m_animTranslate = t; }
        const glm::vec3& GetAnimationTranslate() const { return m_animTranslate; };

        void SetAnimationRotate(const glm::quat& q) { m_animRotate = q; }
        const glm::quat& GetAnimationRotate() const { return m_animRotate; }

        void SetIKRotate(const glm::quat& ikr) { m_ikRotate = ikr; }
        const glm::quat& GetIKRotate() const { return m_ikRotate; }

        void SetLocalTransform(const glm::mat4& m) { m_local = m; }
        const glm::mat4& GetLocalTransform() const { return m_local; }

        void SetGlobalTransform(const glm::mat4& m) { m_global = m; }
        const glm::mat4& GetGlobalTransform() const { return m_global; }

        void CalculateInverseInitTransform();
        const glm::mat4& GetInverseInitTransform() const { return m_inverseInit; }

        // 计算变换矩阵
        glm::vec3 AnimateTranslate() const { return m_animTranslate + m_translate; }
        glm::quat AnimateRotate() const { return m_animRotate * m_rotate; }
        
        MMDNode* GetParent() const { return m_parent; }
        MMDNode* GetChild() const { return m_child; }
        MMDNode* GetNext() const { return m_next; }
        MMDNode* GetPrev() const { return m_prev; }


        // 初始化
        void SaveInitialTRS()
        {
            m_initTranslate = m_translate;
            m_initRotate = m_rotate;
            m_initScale = m_scale;
        }
        // 再初始化
        void LoadInitialTRS()
        {
            m_translate = m_initTranslate;
            m_rotate = m_initRotate;
            m_scale = m_initScale;
        }

        const glm::vec3& GetInitialTranslate() const { return m_initTranslate; }
        const glm::quat& GetInitialRotate() const { return m_initRotate; }
        const glm::vec3& GetInitialScale() const { return m_initScale; }

        // 动画属性
        void SaveBaseAnimation()
        {
            m_baseAnimTranslate = m_animTranslate;
            m_baseAnimRotate = m_animRotate;
        }

        void LoadBaseAnimation()
        {
            m_animTranslate = m_baseAnimTranslate;
            m_animRotate = m_baseAnimRotate;
        }

        void ClearBaseAnimation()
        {
            m_baseAnimTranslate = glm::vec3(0);
            m_baseAnimRotate = glm::quat(1, 0, 0, 0);
        }

        const glm::vec3& GetBaseAnimationTranslate() const { return m_baseAnimTranslate; };
        const glm::quat& GetBaseAnimationRotate() const { return m_baseAnimRotate; }

    protected:
        virtual void OnBeginUpdateTransform();
        virtual void OnEndUpdateTransfrom();
        virtual void OnUpdateLocalTransform();

    protected:
        uint32_t        m_index;
        std::string        m_name;
        bool            m_enableIK;

        MMDNode*        m_parent;
        MMDNode*        m_child;
        MMDNode*        m_next;
        MMDNode*        m_prev;

        glm::vec3    m_translate;
        glm::quat    m_rotate;
        glm::vec3    m_scale;

        glm::vec3    m_animTranslate;
        glm::quat    m_animRotate;

        glm::vec3    m_baseAnimTranslate;
        glm::quat    m_baseAnimRotate;

        glm::quat    m_ikRotate;

        glm::mat4        m_local;
        glm::mat4        m_global;
        glm::mat4        m_inverseInit;

        glm::vec3    m_initTranslate;
        glm::quat    m_initRotate;
        glm::vec3    m_initScale;
    };
}
