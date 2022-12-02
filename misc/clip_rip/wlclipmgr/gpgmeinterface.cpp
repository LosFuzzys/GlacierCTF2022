#include <gpgme++/context.h>
#include <gpgme++/global.h>
#include <gpgme++/encryptionresult.h>
#include <gpgme++/decryptionresult.h>

#include "gpgmeinterface.hpp"

GpgMEInterface::GpgMEInterface(const std::string &gpgKeyUserName) :
    gpgKeyUserName_{gpgKeyUserName}
{
    GpgME::initializeLibrary();
    GpgME::EngineInfo info = GpgME::engineInfo(GpgME::Protocol::OpenPGP);
    if (info.isNull())
        throw std::runtime_error("No default gpg engine for OpenPGP!");

    context_ = GpgME::Context::create(GpgME::Protocol::OpenPGP);
    if (!context_)
        throw std::runtime_error("Failed to set up the gpg api!");

    getKey();
}

std::vector<char>
GpgMEInterface::encrypt(const char *buf,
        const size_t size) const
{
    const GpgME::Data toEncrypt{buf, size};
    GpgME::Data res;

    GpgME::EncryptionResult encryptRes = context_->encrypt(
            std::vector<GpgME::Key>{key_},
            toEncrypt,
            res,
            GpgME::Context::EncryptionFlags::None
    );
    throwIfError(encryptRes.error(), "Encrypting data failed!");
    const size_t resSize = res.toString().size();

    if (res.type() != GpgME::Data::Type::PGPEncrypted)
        std::cout << "Encrypted data has unexpected type!" << std::endl;

    std::vector<char> resData(resSize);
    res.read(resData.data(), resSize);

    return resData;
}

std::vector<char>
GpgMEInterface::decrypt(const char *buf, const size_t size) const
{
    const GpgME::Data toDecrypt{buf, size};
    GpgME::Data res;

    if (toDecrypt.type() != GpgME::Data::Type::PGPEncrypted)
    {
        std::cout << "Trying to decrypt data with an unexpected type";
        std::cout << std::endl;
    }

    GpgME::DecryptionResult decryptRes = context_->decrypt(toDecrypt, res);
    throwIfError(decryptRes.error(), "Decrypting data failed!");
    const size_t resSize = res.toString().size();

    std::vector<char> resData(resSize);
    res.read(resData.data(), resSize);

    return resData;
}

void
GpgMEInterface::getKey()
{
    GpgME::Error err;
    context_->setKeyListMode(GpgME::KeyListMode::WithSecret);
    err = context_->startKeyListing();
    throwIfError(err, "Gpg key listing failed!");

    GpgME::KeyListResult keyListRes = context_->keyListResult();
    if (keyListRes.isNull())
        throwIfError(keyListRes.error(),
                "No gpg keys to incypt your clipboard!");

    GpgME::Key currKey;
    do
    {
        currKey = context_->nextKey(err);
        throwIfError(err, "Failed to get the next gpg key!");
        if (currKey.canEncrypt() && currKey.hasSecret())
        {
            if (gpgKeyUserName_.empty())
            {
                key_ = currKey;
                break;
            }
            else
            {
                if (findUserNameInKey(currKey, gpgKeyUserName_))
                {
                    key_ = currKey;
                    break;
                }
            }
        }
    } while (!currKey.isNull());

    if (key_.isNull())
    {
        throw std::runtime_error("Did not find a valid key!");
    }
}

bool
GpgMEInterface::findUserNameInKey(const GpgME::Key &currKey,
        const std::string &userName) const noexcept
{
    std::vector<GpgME::UserID> userIDs = currKey.userIDs();
    return (std::find_if(userIDs.begin(), userIDs.end(),
        [&](const GpgME::UserID &uid)
        {
            return (uid.name() == userName);
        }
    )) != userIDs.end();
}

void
GpgMEInterface::throwIfError(const GpgME::Error &err,
        const std::string &msg) const
{
    if (err)
    {
        std::cerr << err << std::endl;
        throw std::runtime_error(msg);
    }
}
