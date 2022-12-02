#ifndef __WLCLIPMGR_PROCBLOCK_HPP
#define __WLCLIPMGR_PROCBLOCK_HPP

#include <string>
#include <vector>

#include <iostream>

struct procInfo_m
{
    const std::string name_;
    const size_t age_;
    std::vector<std::string> args_;
    procInfo_m(const std::string name, const size_t age)
        : name_{name}, age_{age}
    {
        args_.push_back(name);
    }
    bool matches(const procInfo_m &other) const
    {
        for (const auto &arg : args_)
        {
            if ((arg.find(other.name_) != std::string::npos) && age_ < other.age_)
                return true;
        }
        return false;
    }
};

// Check if smth blocks copying the clipbaord
bool clipboardProcBlock(const std::string &blockString);

std::vector<procInfo_m> parseBlockOpt(const std::string blockStr,
        size_t &newerThanMax); // parse the block argument string
unsigned long long getUpTime(void); // get /proc/uptime
long procps_hertz_get(void); // get system hertz (ripped from procps)


#endif //__WLCLIPMGR_PROCBLOCK_HPP

