#pragma once

#include <string>
#include <vector>

namespace utils {
    bool isValid(
        const std::wstring_view message, const std::vector<std::wstring_view>& words,
        size_t indexBegin, size_t indexEnd
    );

    std::wstring s2w(const std::string_view& str);

    std::string w2s(const std::wstring_view& wstr);

    void removeCharsFromStr(std::wstring& target, const std::vector<wchar_t>& charsToRemove);
}  // namespace utils