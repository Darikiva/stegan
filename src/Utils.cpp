#include "Utils.h"
#include "CharsTable.h"

#include <locale>
#include <codecvt>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <clocale>

bool utils::isValid(
    const std::wstring_view message, const std::vector<std::wstring_view>& words, size_t indexBegin,
    size_t indexEnd
)
{
    // std::setlocale(LC_CTYPE, "ukr");

    std::string res;
    std::vector<std::wstring> strs;

    boost::split(strs, message, boost::is_any_of(" "));

    std::wofstream f("C:/Users/darik/univer/diploma/test_validity.txt", std::ios_base::app);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    f.imbue(loc);

    f << std::endl << std::endl;

    auto it = words.begin() + indexBegin;

    auto itEnd = words.begin() + indexEnd;

    for (auto& str: strs) {
        auto newEnd = std::remove_if(str.begin(), str.end(), [] (const auto ch) {
            return ch == L'\"';
        });
        str.erase(newEnd, str.end());

        if (it == words.end() || it == itEnd) {
            return true;
            // for (size_t i = 1; i < 4 && i < str.size(); ++i) {
            //     if (usedLetters.find(str.substr(0, i)) != usedLetters.end()) {
            //         return false;
            //     }
            // }
            // continue;
        }

        auto substr = str.substr(0, it->size());

        std::wstring substrLowercase;

        for (const auto& wch: substr) {
            substrLowercase += static_cast<wchar_t>(std::tolower(static_cast<int>(wch)));
        }
        f << L"next word: " << str << L", " << *it << L'\n';

        f << L"substr: " << substrLowercase << L'\n';
        if (substrLowercase == *it) {
            ++it;
        } else {
            for (size_t i = 1; i < 4 && i < str.size(); ++i) {
                if (usedLetters.find(str.substr(0, i)) != usedLetters.end()) {
                    return false;
                }
            }
        }
    }

    if (it != itEnd) {
        f << L"last word = " << *it << std::endl;
    }

    f.close();

    return it == words.end() || it == itEnd;
}

std::wstring utils::s2w(const std::string_view& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(std::string{str});
}

std::string utils::w2s(const std::wstring_view& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(std::wstring{wstr});
}

void utils::removeCharsFromStr(std::wstring& target, const std::vector<wchar_t>& charsToRemove)
{
    auto newEnd = std::remove_if(target.begin(), target.end(), [&](const wchar_t& wch) {
        return std::any_of(charsToRemove.begin(), charsToRemove.end(), [&](const auto& charToRemove) {
            return wch == charToRemove;
        });
    });
    target.erase(newEnd, target.end());
}
