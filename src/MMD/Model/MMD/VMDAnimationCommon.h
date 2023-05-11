#pragma once

// 文件基于博客 https://blog.csdn.net/haseetxwd/article/details/82821533
//             https://blog.csdn.net/weixin_39797393/article/details/110736866

#include <cstdint>
#include <vector>

namespace mmd
{
    template <typename KeyType>
    typename std::vector<KeyType>::const_iterator FindBoundKey(
        const std::vector<KeyType>&    keys,
        int32_t                        t,
        size_t                        startIdx
    ) {
        if (keys.empty() || keys.size() <= startIdx)
        {
            return keys.end();
        }

        const auto& key0 = keys[startIdx];
        if (key0.m_time <= t)
        {
            if (startIdx + 1 < keys.size())
            {
                const auto& key1 = keys[startIdx + 1];
                if (key1.m_time > t)
                {
                    return keys.begin() + startIdx + 1;
                }
            }
            else
            {
                return keys.end();
            }
        }
        else
        {
            if (startIdx != 0)
            {
                const auto& key1 = keys[startIdx - 1];
                if (key1.m_time <= t)
                {
                    return keys.begin() + startIdx;
                }
            }
            else
            {
                return keys.begin();
            }
        }

        auto bundIt = std::upper_bound(keys.begin(), keys.end(), t, [](int32_t lhs, const KeyType& rhs) {
            return lhs < rhs.m_time;
        });
        return bundIt;
    }
}
