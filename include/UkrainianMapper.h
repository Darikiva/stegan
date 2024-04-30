#pragma once

#include "MapperAbstract.h"

class UkrainianMapper : public MapperAbstract
{
public:
    auto mapMessage(std::string_view cipheredMessage) const -> std::vector<std::wstring_view> final;
    auto demapMessage(std::wstring_view message) const -> std::string final;
};