#pragma once

// 由于模型文件多含有日文，故加入日文编码转换防止出错

// 文件基于博客 https://blog.csdn.net/hellofeiya/article/details/8441812
//             https://www.mk-mode.com/blog/2014/08/24/cpp-convert-sjis-to-utf8/

#include <string>

namespace mmd
{
    char16_t ConvertSjisToU16Char(int ch);
    std::u16string ConvertSjisToU16String(const char* sjisCode);
    std::u32string ConvertSjisToU32String(const char* sjisCode);
}
