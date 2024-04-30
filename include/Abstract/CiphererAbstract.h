#pragma once

#include <string>

class CiphererAbstract
{
public:
    virtual std::string cipherMessage(std::string_view message) const = 0;
    virtual std::string decipherMessage(std::string_view cipheredMessage) const = 0;

    virtual ~CiphererAbstract() = default;
};