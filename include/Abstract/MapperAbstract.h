#pragma once

#include <string>
#include <vector>

class MapperAbstract
{
public:
    virtual auto mapMessage(std::string_view cipheredMessage) const -> std::vector<std::wstring_view> = 0;
    virtual auto demapMessage(std::wstring_view message) const -> std::string = 0;

    virtual ~MapperAbstract() = default;
};