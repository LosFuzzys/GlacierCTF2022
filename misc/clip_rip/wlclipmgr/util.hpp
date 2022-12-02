#ifndef __WLCLIPMGR_UTIL_HPP
#define __WLCLIPMGR_UTIL_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

inline std::vector<std::string>
stringSplit(const std::string &s, const char delim)
{
    std::vector<std::string> res;
    std::istringstream oss{s};
    for (std::string token; std::getline(oss, token, delim); )
        res.push_back(token);
    return res;
}

#endif //__WLCLIPMGR_UTIL_HPP
