#ifndef __WLCLIPMGR_GPGME_AGENT_HPP
#define __WLCLIPMGR_GPGME_AGENT_HPP

#include <gpgme++/context.h>
#include <gpgme++/data.h>
#include <gpgme++/key.h>
#include <gpgme++/keylistresult.h>
#include <gpgme++/engineinfo.h>

class GpgMEInterface
{
    const std::string gpgKeyUserName_;

    void getKey();
    bool findUserNameInKey(const GpgME::Key &currKey,
            const std::string &userName) const noexcept;
    void throwIfError(const GpgME::Error &err, const std::string &msg) const;

    public:
    GpgMEInterface(const std::string &gpgKeyUserName);

    std::vector<char> encrypt(const char *buf, const size_t size) const;
    std::vector<char> decrypt(const char *buf, const size_t size) const;

    protected:
    std::unique_ptr<GpgME::Context> context_;
    GpgME::Key key_;
};

#endif // __WLCLIPMGR_GPGME_AGENT_HPP
