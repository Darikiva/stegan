#include "GptPrompter.h"

#include <codecvt>
#include <fmt/format.h>
#include <fstream>


#include "Utils.h"
#include "openai.h"

namespace {
    constexpr size_t C_STEP = 10;
    constexpr auto defaultSystemMessage
        = "You are an ukrainian man, every letter in your responses is in lower case";
}

auto GptPrompter::proceed(const std::vector<std::wstring_view>& words) -> std::wstring
{
    std::wofstream f("C:/Users/darik/univer/diploma/test.txt");
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    f.imbue(loc);

    for (const auto& word : words) {
        f << word << " ";
    }

    openai::start("");

    nlohmann::json j;
    j["model"] = "gpt-3.5-turbo";

    nlohmann::json messages;

    auto addMessage = [&](std::string message, std::string role) {
        nlohmann::json messageJson;

        f << L"role=" << utils::s2w(role) << L" content=" << utils::s2w(message) << '\n';

        messageJson["role"] = std::move(role);
        messageJson["content"] = std::move(message);


        messages.push_back(std::move(messageJson));
    };

    auto fillMessageWithWords = [&](size_t beg, std::wstring_view messageBegin) -> std::wstring {
        bool isFirst = true;

        std::wstring res{messageBegin};

        for (size_t i = beg; i < beg + C_STEP && i < words.size(); ++i) {
            if (!isFirst) {
                res += L", наступне на \"";
            }
            res += words[i];
            res += L"\"";

            isFirst = false;
        }

        return res;
    };

    size_t indexBegin = 0;

    {
        std::wstring content = fillMessageWithWords(
            indexBegin, L"Згенеруй побутову історію, яка складається з " + std::to_wstring(C_STEP)
                            + L" слів, і в якій перше слово починається на "
        );

        addMessage(defaultSystemMessage, "system");
        addMessage(utils::w2s(content), "user");
    }

    size_t counter = 0;

    std::wstring res;

    while (counter < 30 && indexBegin < words.size()) {
        j["messages"] = messages;

        auto completion = openai::chat().create(j);
        std::wstring responseWstr = [&completion]() {
            std::string resp = completion["choices"][0]["message"]["content"];
            return utils::s2w(resp);
        }();

        f << L"response=" << responseWstr << std::endl;

        if (!utils::isValid(responseWstr, words, indexBegin, indexBegin + C_STEP)) {
            ++counter;
        }
        else {
            utils::removeCharsFromStr(responseWstr, {L'\"', L','});

            res += responseWstr;
            res += L" ";
            indexBegin += C_STEP;
            messages.clear();

            std::wstring content = L"Згенеруй продовження історії, яке буде складатись з "
                                 + std::to_wstring(C_STEP) + L" слів. Історія починається так \"";
            content += res;
            content += L"\". Кожне наступне слово продовження повинно починатись на \"";
            content = fillMessageWithWords(indexBegin, content);

            addMessage(defaultSystemMessage, "system");
            addMessage(utils::w2s(content), "user");
        }
    }

    f << L"res=" << res << std::endl;

    f.close();

    return res;
}