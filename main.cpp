#include <iostream>

#include "Poco/Crypto/Crypto.h"

#include "MyEngine.h"

#include "RsaCipherer.h"
#include "UkrainianMapper.h"
#include "GptPrompter.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>

int main(int argc, char* argv[])
{
    std::wofstream f("C:/Users/darik/univer/diploma/res.txt");
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    f.imbue(loc);

    MyEngine engine;
    // auto wow = engine.hideMessage(L"Повідомлення прикриття", L"Привіт, світ!");

    // prompter->proceed({L"к", L"п", L"р", L"а", L"о"});


    // std::wstring coverMessage, secretMessage;

    // MyEngine engine;

    auto cipher = std::make_unique<RsaCipherer>();
    auto mapper = std::make_unique<UkrainianMapper>();
    auto prompter = std::make_unique<GptPrompter>();

    // std::string message = "hello, world!";
    std::wstring message = L"Якийсь секрет";

    auto cipheredMessage = cipher->cipherMessage(utils::w2s(message));

    for (char ch: cipheredMessage) {
        std::cout << static_cast<int>(ch) << " ";
    }

    std::cout << std::endl;

    std::cout << cipheredMessage.size() << std::endl;

    auto mappedStrs = mapper->mapMessage(cipheredMessage);

    std::cout << mappedStrs.size() << std::endl;

    for (auto wow: mappedStrs) {
        f << wow << L" ";
    }

    // auto prompterRes = prompter->proceed(mappedStrs);

    // f << L"prompter res=" << prompterRes << std::endl;

    // auto prompterRes
    //     = L"музей супутник шанував експозицію утнувши чотири залози страшенно отруївшись потом. "
    //       L"насмішило дерзке стремління татарина коригувати двома синіми стамбулами багатщину "
    //       L"завжди. подружжя ледь незбагненно віддавали фарби багатющі закінчили ними зрозумілу "
    //       L"обмінювались щиро. ридкісно помітні сліди чуєш оком барвисту хвилю життя усміхається "
    //       L"хлопець. відважне одначеє дерзання трагічно затоптане однаковістю руйнує упередженості "
    //       L"змінюючи луну. пишні утопчані задуму відгукуються кудибудь шпурскати сміливістю "
    //       L"скованістью глибинними утішностями. поошарпаний увертання вступили впіймавши";

    // auto cipheredMessage = mapper->demapMessage(prompterRes);

    // for (const auto ch: cipheredMessage) {
    //     std::cout << static_cast<int>(ch) << " " ;
    // }

    // std::cout << std::endl;

    // std::cout << cipheredMessage.size() << std::endl;

    // auto decipheredMessage = cipher->decipherMessage(cipheredMessage);

    // std::cout << decipheredMessage << " " << decipheredMessage.size() << std::endl;

    // std::cout << (static_cast<char>(-13)) << " " << static_cast<char>(-13+128) << std::endl;
    // f << L"Wow=" << utils::s2w(decipheredMessage) << std::endl;

    // std::wstring wstrMapped;

    // for (const auto& str: mappedStrs) {
    //     // std::cout << static_cast<char>(std::stoi(std::wstring{str})) << " ";
    //     wstrMapped += str;
    //     wstrMapped += L" ";
    // }

    // std::wcout << wstrMapped << std::endl;
    // std::cout << mapper->demapMessage(wstrMapped);

    // std::wcout << std::endl;

    // {  // hiding
    //     auto outputMessage = engine.hideMessage(coverMessage, secretMessage);
    // }

    // {  // detection
    //     auto secretMessage = engine.detectMessage(coverMessage);
    // }

    f.close();

    return 0;
}