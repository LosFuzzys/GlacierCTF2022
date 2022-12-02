/*  This code was modified to be a CTF challenge.
    Thats why some stuff is unused and everything is a bit bloated.
    Can you still figure out how to get the flags?
    Good luck and have fun.
*/
#include <iostream>
#include <fstream>
#include <vector>

#include "clipboard.hpp"
#include "util.hpp"
// My new fav argparser for cpp. slightly *improved* version.
#include "thirdParty/argparse/include/argparse/argparse.hpp"

std::string
getFallbackPageName()
{
    time_t now = std::time(0);
    tm *ltm = std::localtime(&now);
    std::stringstream ss;
    std::string year{std::to_string(ltm->tm_year)};
    ss << "clip";
    ss << std::setfill('0') << std::setw(2) << ltm->tm_mday;
    ss << std::setfill('0') << std::setw(2) << ltm->tm_mon;
    ss << std::string(year.end()-2, year.end());
    return ss.str();
}

enum Command
{
    store,
    watch,
    list,
    restore,
    replr
};

struct Args : public argparse::Args
{
    Command &command = arg("command for wlclipmgr");
    std::string &page = kwarg("p,page", "clipboard page").set_default("");
    size_t &index = kwarg("i,index", "page index to restore").set_default(0);
    size_t &lines = kwarg("l,lines", "how many lines to list").set_default(10);
    std::string &block = kwarg("b,block",
        "block saving the cliboard if a certain process is running")
        .set_default("");
    /*
        Example: pass:10,scary_app | This will not save the clipboard
        if there is a process newer than 10 seconds and its cmdline
        has "pass" in it,
        or if there is a process that has \"scary_app\" in its cmdline
    */
    std::string &gpgUserName = kwarg("u,gpg-user",
        "user name of the gpg key to use, when de-/encypting")
        .set_default("");
    /*
       if not provided, the first key, that can encrypt and has a
       secret will be used. (to list your keys, use gpg(2) --list-keys))
    */
};

void
doWatch(const Args &args)
{
    std::stringstream command;
    command << "wl-paste";
    command << " -w wlclipmgr store";
    if (!args.page.empty())
        command << " --page " << args.page;
    if (!args.block.empty())
        command << " --block \"" << args.block << '\"';
    std::system(command.str().c_str());
}

void
replrRun(Clipboard &clipboard)
{
    while(std::cin.good())
    {
        Args replrArgs;
        std::string line;

        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::vector<std::string> words = stringSplit(line, ' ');
        std::vector<const char *> argvVec = { "lul" };

        for (const auto &a : words)
            argvVec.push_back(a.c_str());

        if (argvVec.size() < 2)
        {
            std::cout << "Duh? I need a command!" << std::endl;
            continue;
        }

        if (strcmp(argvVec[1], "quit") == 0 || *argvVec[1] == 'q')
        {
            //clipboard.writePage();
            return;
        }

        const auto printReplrArgHelp = []()
        {
            std::cout << "allowed: <store, list, restore>" << std::endl;
            std::cout << "-l,--lines : how many lines to list [default: 10]"
              << std::endl;
            std::cout << "-i,--index : page index to restore [default: 0]"
              << std::endl;
        };

        try
        {
            replrArgs.parse(argvVec.size(), argvVec.data(), true);
        } catch (const std::runtime_error &err)
        {
            printReplrArgHelp();
            continue;
        }
        switch(replrArgs.command)
        {
            case Command::store:
                clipboard.addReplrEntry();
                break;
            case Command::list:
                // only recent history
                if (replrArgs.lines > 100)
                {
                  std::cout << "Can only list the last 100 entries!" << std::endl;
                  break;
                }
                clipboard.listEntries(replrArgs.lines);
                break;
            case Command::restore:
                // only recent history
                if (replrArgs.index > 100)
                {
                  std::cout << "Can only restore up to index 100!" << std::endl;
                  break;
                }
                clipboard.restore(replrArgs.index, false);
                break;
            default:
                printReplrArgHelp();
                break;
        }
    }
}

int
run(const Args &args, const fs::path &cacheDir)
{
    std::string page;
    if (args.page.empty())
        page = getFallbackPageName();

    else page = args.page;

    Clipboard clipboard{
        cacheDir / (page + ".gpg"),
        cacheDir / (page + "-tmpfile"),
        args.gpgUserName,
    };

    try
    {
        switch(args.command)
        {
            case Command::store:
                clipboard.loadPage();
                clipboard.addEntry(args.block);
                clipboard.writePage();
                break;
            case Command::list:
                clipboard.loadPage();
                clipboard.listEntries(args.lines);
                break;
            case Command::restore:
                clipboard.loadPage();
                clipboard.restore(args.index);
                break;
            case Command::watch:
                doWatch(args);
                break;
            case Command::replr:
                clipboard.loadPage();
                replrRun(clipboard);
                break;
        }
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}


int
main(int argc, char *argv[])
{
    std::setvbuf(stdin,0,2,0);
    std::setvbuf(stdout,0,2,0);

    fs::path cacheDir;
    const char *xdgVar = std::getenv("XDG_DATA_HOME");
    if (xdgVar == NULL)
    {
        xdgVar = std::getenv("HOME");
        if (xdgVar == NULL)
        {
            std::cerr << "Fatal: env $HOME not found!" << std::endl;
            return -1;
        }
        // lets just assume this exists
        cacheDir = fs::path(std::string(xdgVar) + "/.local/share/");
        if (!fs::exists(cacheDir))
          fs::create_directories(cacheDir);
    }
    else
        cacheDir = fs::path(xdgVar);

    cacheDir = cacheDir / "wlclipmgr";

    if (!fs::exists(cacheDir))
        fs::create_directory(cacheDir);

    Args args = argparse::parse<Args>(argc, argv);

    return run(args, cacheDir);
}
