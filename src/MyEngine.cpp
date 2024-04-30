#include "MyEngine.h"

#include "GptPrompter.h"
#include "RsaCipherer.h"
#include "UkrainianMapper.h"
#include "Utils.h"

MyEngine::MyEngine()
    : cipherer{std::make_unique<RsaCipherer>()},
      mapper{std::make_unique<UkrainianMapper>()},
      prompter{std::make_unique<GptPrompter>()}
{}

auto MyEngine::hideMessage(std::wstring_view coverMessage, std::wstring_view secretMessage)
    -> std::wstring
{
    auto cipheredMessage = cipherer->cipherMessage(utils::w2s(secretMessage));
    auto mappedWords = mapper->mapMessage(cipheredMessage);

    return [&, this]() -> std::wstring {
        auto res = prompter->proceed(mappedWords);

        // while (!utils::isValid(res, mappedWords)) {
        //     res = prompter->proceed(mappedWords);
        // }

        return res;
    }();
}

auto MyEngine::detectMessage(std::wstring_view coverMessage) -> std::wstring
{
    auto cipheredMessage = mapper->demapMessage(coverMessage);
    return utils::s2w(cipherer->decipherMessage(cipheredMessage));
}