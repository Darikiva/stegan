#pragma once

#include "PrompterAbstract.h"
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>

class GptPrompter: public PrompterAbstract
{
public:
    auto proceed(const std::vector<std::wstring_view>& words) -> std::wstring final;
};