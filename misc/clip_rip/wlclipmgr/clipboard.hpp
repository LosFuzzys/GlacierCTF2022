#ifndef __WLCIPMGR_CLIPBOARD_HPP
#define __WLCIPMGR_CLIPBOARD_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <filesystem>
namespace fs = std::filesystem;

#include <msgpack.hpp>

#define MAX_SIZE_CLIPBOARD_ENTRY 0x1000
#define MIN_SIZE_COPY_VIA_FILE 0x100
#define OUTPUT_LINE_TRUNCATE_AFTER 70

class ClipboardEntry
{
    std::vector<char> buffer_;
    size_t size_;
    std::string mime_;
    bool redact_;

    ClipboardEntry(const std::vector<char> &input, const size_t inputSize,
            bool redact) :
        buffer_{input}, size_{inputSize}, redact_{redact}
    {
        setMimeType();
    }

    friend std::ostream &operator<<(std::ostream &os,
            const ClipboardEntry &obj);
    friend std::ofstream &operator<<(std::ofstream &os,
            const ClipboardEntry &obj);
    friend class Clipboard;

    public:
    ClipboardEntry() = default;

    bool isPrintable() const noexcept;

    bool operator==(const ClipboardEntry &other) const noexcept;
    const ClipboardEntry &setMimeType();

    MSGPACK_DEFINE(buffer_, size_, mime_, redact_);
};

class Clipboard
{
    const fs::path pagePath_;
    const fs::path tmpFilePath_;
    std::deque<ClipboardEntry> entries_;

    const std::string gpgUserName_;

    void encryptWritePage(const msgpack::sbuffer &sbuf) const noexcept;
    void decryptLoadPage(const std::vector<char> &data) noexcept;

    public:
    Clipboard(const fs::path &pagePath, const fs::path &tmpFilePath,
            const std::string &gpgUserName) :
        pagePath_{pagePath}, tmpFilePath_{tmpFilePath}, gpgUserName_{gpgUserName}
    {
    }

    ~Clipboard() = default;

    void addReplrEntry();
    void addEntry(const std::string &block);
    void listEntries(const size_t num);
    void restore(const size_t index, bool wlcopy=true);

    void unpackEntries(const std::vector<char> &data);
    void writePage() const;
    void loadPage();
};


#endif // __WLCIPMGR_CLIPBOARD_HPP
