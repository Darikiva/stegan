#include "RsaCipherer.h"
#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/RSAKey.h>

#include <memory>
#include <exception>

namespace {
    /// @todo create unique key pairs every time
    constexpr auto publicKey = R"(-----BEGIN PUBLIC KEY-----
MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAIalu0KbOSu0SY/TeGe5+XxWKm3cNLSQ
RSowCObJm5UrOqh9vkSfEdc+n0vA3+Jwb3wXZ5y2jvjHt1ku4n5BWWECAwEAAQ==
-----END PUBLIC KEY-----)";

    constexpr auto privateKey = R"(-----BEGIN RSA PRIVATE KEY-----
MIIBOwIBAAJBAJaH6pgrijJvVyLF8VSDdSJ43mcRJ9MOyfcXMv16R9JCrWD2a9pr
PuqvjLilcwKkiI8kbbbom7mUeg0t9KKJAKUCAwEAAQJAWXDQtzHHn0gAoiyyw+CI
DL98hgjvfLxgzGwAZBPv8MG0y8T/SgP3KZH4v2aIsAPmSHCUCvWx6Lx1gRVrdj7r
AQIhAPxhu0y7L7y/HoEa3F0h14KSzcHRN6Ojj/MsDnEaxKKRAiEAmLBhkuMmJc40
i0dTfDwtumgBYzc5+FU+/xJ9SOq03tUCIQDaJIdF7U13sSHmqZbrEMM74zPhYLrc
wBU+NEhPTrnDYQIgefVwin4LC2lwiMs5AOOkdt76NMB4+kVE40Jmdeaa/90CIQCa
g3NfS4NmFwTFa0Y0kB5XDI/JrQtbC91X4EIQ+Y/f4g==
-----END RSA PRIVATE KEY-----)";

}

auto RsaCipherer::cipherMessage(std::string_view message) const -> std::string
{
    auto keyStream = std::istringstream{publicKey};
    auto key = Poco::Crypto::RSAKey{&keyStream};

    auto cipher = std::unique_ptr<Poco::Crypto::Cipher>{
        Poco::Crypto::CipherFactory::defaultFactory().createCipher(key)
    };

    return cipher->encryptString(std::string{message}, Poco::Crypto::Cipher::ENC_BASE64_NO_LF );
}

auto RsaCipherer::decipherMessage(std::string_view cipheredMessage) const -> std::string
{
    auto keyStream = std::istringstream{privateKey};

    try {
        const auto key = Poco::Crypto::RSAKey{nullptr, &keyStream};
        auto cipher = std::unique_ptr<Poco::Crypto::Cipher>{
            Poco::Crypto::CipherFactory::defaultFactory().createCipher(key)
        };

        return cipher->decryptString(
            std::string{cipheredMessage}, Poco::Crypto::Cipher::ENC_BASE64_NO_LF
        );
    } catch (Poco::Exception& ex) {
        throw;
    }
}
