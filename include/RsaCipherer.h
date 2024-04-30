#pragma once

#include "CiphererAbstract.h"

class RsaCipherer : public CiphererAbstract
{
public:
    auto cipherMessage(std::string_view message) const -> std::string final;
    auto decipherMessage(std::string_view cipheredMessage) const -> std::string final;
};