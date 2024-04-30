#pragma once

#include "CiphererAbstract.h"
#include "MapperAbstract.h"
#include "PrompterAbstract.h"

#include <memory>

class MyEngine
{
public:
    MyEngine();

    auto hideMessage(std::wstring_view coverMessage, std::wstring_view secretMessage) -> std::wstring;
    auto detectMessage(std::wstring_view coverMessage) -> std::wstring;

private:
    std::unique_ptr<CiphererAbstract> cipherer;
    std::unique_ptr<MapperAbstract> mapper;
    std::unique_ptr<PrompterAbstract> prompter;
};