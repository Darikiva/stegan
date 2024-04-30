#include "UkrainianMapper.h"
#include "CharsTable.h"

#include <boost/algorithm/string.hpp>
#include <map>
#include <unordered_map>
#include <iostream>

auto UkrainianMapper::mapMessage(std::string_view cipheredMessage
) const -> std::vector<std::wstring_view>
{
    std::vector<std::wstring_view> res;

    for (char ch : cipheredMessage) {
        res.push_back(charToLetters.at(ch));
    }

    return res;
}

auto UkrainianMapper::demapMessage(std::wstring_view message) const -> std::string
{
    std::string res;
    std::vector<std::wstring> strs;

    boost::split(strs, message, boost::is_any_of(" "));

    for (const auto& str : strs) {
        for (const auto& [ch, wch]: charToLetters) {
            if (str.substr(0, wch.size()) == wch) {
                res += ch;
                break;
            }
        }
    }

    return res;
}
