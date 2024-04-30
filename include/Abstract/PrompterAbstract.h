#pragma once

#include <vector>
#include <string>

class PrompterAbstract
{
public:
    virtual auto proceed(const std::vector<std::wstring_view>& words) -> std::wstring = 0;

    virtual ~PrompterAbstract() = default;
};