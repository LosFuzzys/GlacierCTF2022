#include <istream>
#include <unordered_map>

#include <cctype> // used for isprint()

#include "clipboard.hpp"
#include "procblock.hpp"
#include "gpgmeinterface.hpp"

extern "C" {
#include "thirdParty/xdgmime/src/xdgmime.h"
}

void
Clipboard::addReplrEntry()
{
    std::freopen(NULL, "rb", stdin);
    std::vector<char> buffer;

    std::cout << "Please enter size of the entry" << std::endl;
    unsigned int input_size;
    scanf("%u\n", &input_size);

    if (input_size > MAX_SIZE_CLIPBOARD_ENTRY)
    {
      std::cout << "Thats too much for me!" << std::endl;
      return;
    }

    try
    {
        char c;
        while (std::cin.read(&c, 1),
            std::cin.good() && buffer.size() < input_size)
        {
            buffer.push_back(c);
        }
    } catch (const std::ios::failure &err) {
        std::cerr << "Failed to read clipboard content!" << std::endl;
        std::cerr << err.what() << std::endl;
        return;
    }
    std::freopen(NULL, "r", stdin);

    if (buffer.size() == 0)
        return;

    ClipboardEntry newEntry{buffer, buffer.size(), false};

    if (entries_.empty() || newEntry != entries_[0])
        entries_.push_front(newEntry);
}

void
Clipboard::addEntry(const std::string &block)
{
    bool redact = !block.empty() && clipboardProcBlock(block);

    std::freopen(NULL, "rb", stdin);
    std::vector<char> buffer;
    try
    {
        buffer = std::vector<char>{
            std::istreambuf_iterator<char>{std::cin}, {}
        };
    } catch (const std::ios::failure &err) {
        std::cerr << "Failed to read clipboard content!" << std::endl;
        std::cerr << err.what() << std::endl;
        return;
    }
    std::freopen(NULL, "r", stdin);

    if (buffer.size() == 0)
        return;

    ClipboardEntry newEntry{buffer, buffer.size(), redact};

    if (entries_.empty() || newEntry != entries_[0])
        entries_.push_front(newEntry);
}

void
Clipboard::listEntries(const size_t num)
{
    for (size_t index = 0; index < num && index < entries_.size(); index++)
    {
        const ClipboardEntry &entry = entries_[index];

        if (index == 0)
          std::cout << "Current: ";
        else
          std::cout << index << " ";
        std::cout << entry << std::endl;
    }
}

void
Clipboard::restore(const size_t index, bool wlcopy)
{
    if (index == 0 || index >= entries_.size())
    {
        std::cout << "Nothing to restore" << std::endl;
        return;
    }
    const ClipboardEntry entry = entries_[index];
    entries_.erase(std::next(entries_.begin(), index));

    if (!wlcopy)
    {
      if (entries_.empty() || entry != entries_[0])
          entries_.push_front(entry);
      writePage();
      return;
    }

    writePage();

    std::stringstream copyCmd;
    copyCmd << "wl-copy";

    if (entry.size_ > MIN_SIZE_COPY_VIA_FILE || !entry.isPrintable())
    {
        try
        {
            std::ofstream tmpFile{tmpFilePath_, std::ios::out | std::ios::binary};
            tmpFile << entry;
            tmpFile.close();
        }
        catch (const std::exception &err)
        {
            std::cerr << "Failed to write entry to tmpfile." << std::endl;
            return;
        }
        copyCmd << " < ";
        copyCmd << tmpFilePath_.string();
        if (std::system(copyCmd.str().c_str()) != 0)
        {
            std::cerr << "Copy file command failed:" << std::endl;
            std::cerr << copyCmd.str() << tmpFilePath_.string() << std::endl;
        }
    }
    else
    {
        copyCmd << '\"';
        const std::string &prefix = copyCmd.str();
        std::vector<char> command{prefix.begin(), prefix.end()};

        command.insert(command.end(), entry.buffer_.begin(), entry.buffer_.end());
        command.push_back('\"');
        command.push_back('\0');

        if (std::system(command.data()) != 0)
        {
            std::cerr << "Copy command failed:" << std::endl;
            std::cerr << '\t' << command.data() << std::endl;
        }
    }
}

void
Clipboard::unpackEntries(const std::vector<char> &data)
{
    if (data.empty())
        return;

    msgpack::object_handle oh = msgpack::unpack(data.data(), data.size());
    msgpack::object obj = oh.get();

    obj.convert(entries_);
};

void
Clipboard::encryptWritePage(const msgpack::sbuffer &sbuf) const noexcept
{
    const GpgMEInterface gpgInterface{gpgUserName_};
    std::vector<char> res = gpgInterface.encrypt(sbuf.data(), sbuf.size());

    std::ofstream outFile{pagePath_.string(), std::ios::out | std::ios::binary};

    outFile.write(res.data(), res.size());
    outFile.close();
}

void
Clipboard::decryptLoadPage(const std::vector<char> &data) noexcept
{
    const GpgMEInterface gpgInterface{gpgUserName_};
    std::vector<char> res = gpgInterface.decrypt(data.data(), data.size());

    unpackEntries(res);
}

void
Clipboard::writePage() const
{
    if (entries_.empty())
    {
        std::cout << "Nothing to write!" << std::endl;
        return;
    }
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, entries_);

    encryptWritePage(sbuf);
}

void
Clipboard::loadPage()
{
    if (!fs::exists(pagePath_))
      return;

    std::ifstream pageFile{pagePath_, std::ios::in | std::ios::binary};
    size_t pageSize;
    try
    {
        pageSize = fs::file_size(pagePath_);
    } catch (const fs::filesystem_error &err)
    {
        std::cerr << err.what() << std::endl;
        return;
    }
    if (pageSize == 0)
        return;

    std::vector<char> readBuff(pageSize);
    pageFile.read(readBuff.data(), pageSize);
    pageFile.close();

    decryptLoadPage(readBuff);
}

const ClipboardEntry &
ClipboardEntry::setMimeType()
{
    int res_prio;
    const char *res = xdg_mime_get_mime_type_for_data(buffer_.data(),
            size_, &res_prio);

    mime_ = std::string{res};
    return *this;
}

bool ClipboardEntry::isPrintable() const noexcept
{
    static const std::string textMime = "text";
    if (mime_.empty() || mime_.size() < textMime.size())
        return false;
    if ("text" == mime_.substr(0, textMime.size() - 1))
        return true;
    return false;
}

bool
ClipboardEntry::operator==(const ClipboardEntry &other) const noexcept
{
    if (size_ != other.size_)
        return false;
    if (buffer_ != other.buffer_)
        return false;
    return true;
}

std::ostream &
operator<<(std::ostream &os, const ClipboardEntry &obj)
{
    static const std::unordered_map<char,std::string> substitute
    {
        {'\n', "\\n"}, {'\r', "\\r"}, {'\r', "\\r"}
    };

    if (!obj.mime_.empty() && obj.mime_ != "text/plain")
    {
        os << "mime: [" << obj.mime_ << "] size: " << obj.size_;
        return os;
    }

    if (obj.redact_)
    {
      for (auto i = 0; i < OUTPUT_LINE_TRUNCATE_AFTER; i++)
        os << "█";
      return os;
    }

    const size_t outSize = (obj.size_ < OUTPUT_LINE_TRUNCATE_AFTER) ?
        obj.size_ : OUTPUT_LINE_TRUNCATE_AFTER;

    std::vector<char> outBuffer(obj.buffer_.begin(),
            obj.buffer_.begin() + outSize);

    for (const char c : outBuffer)
    {
        auto it = substitute.find(c);
        if (it != substitute.end())
            os << it->second;
        else if (std::isprint(c))
            os << c;
        else
            os << "█";
    }

    if (outSize == OUTPUT_LINE_TRUNCATE_AFTER)
        os << "... (" << obj.size_ - outSize << " more chars)";

    return os;
}

std::ofstream &
operator<<(std::ofstream &ofs, const ClipboardEntry &obj)
{
    ofs.write(obj.buffer_.data(), obj.buffer_.size());
    return ofs;
}
