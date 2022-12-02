#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <proc/readproc.h>
#include <sys/sysinfo.h>

#include "procblock.hpp"
#include "util.hpp"

bool
clipboardProcBlock(const std::string &blockString)
{
    size_t newerThanMax = 0;
    const auto block = parseBlockOpt(blockString, newerThanMax);
    std::vector<procInfo_m> kanidates;
    const auto uptimeSecs = getUpTime();
    const auto hertz = procps_hertz_get();
    const auto ownPid = getpid();
    PROCTAB *proc = openproc(PROC_FILLSTAT | PROC_FILLCOM);
    while (proc_t *procInfo = readproc(proc, NULL))
    {
        unsigned long long elapsed = 0;
        if (newerThanMax > 0)
        {
            elapsed = (uptimeSecs - (procInfo->start_time / hertz));
            if (elapsed > newerThanMax) continue;
        }
        if (!procInfo->cmdline || !procInfo->cmdline[0]) continue;
        if (procInfo->tid == ownPid) continue;

        procInfo_m procKanidate{procInfo->cmdline[0], elapsed};
        for (size_t i = 0; i < 3; i++)
        {
            if(procInfo->cmdline[i] == NULL) break;
            procKanidate.args_.push_back(std::string(procInfo->cmdline[i]));
        }
        kanidates.push_back(procKanidate);
    }
    closeproc(proc);
    for (const procInfo_m &procKanidate : kanidates)
    {
        for (const procInfo_m &blockingProc : block)
        {
            if (procKanidate.matches(blockingProc))
                return true;
        }
    }
    return false;
}

std::vector<procInfo_m>
parseBlockOpt(const std::string blockStr,
        size_t &newerThanMax)
{
    std::vector<procInfo_m> res;
    for (const auto &procStr : stringSplit(blockStr, ','))
    {
        const auto proc = stringSplit(procStr, ':');
        if (proc.size() == 1)
            res.push_back(procInfo_m{proc[0], 0});
        else if (proc.size() == 2)
        {
            size_t newerThan = 0;
            std::stringstream{proc[1]} >> newerThan;
            // I do not care if newerThan == 0; ignoring errors;
            if (newerThanMax < newerThan) newerThanMax = newerThan;
            res.push_back(procInfo_m{proc[0], newerThan});
        }
    }
    return res;
}

unsigned long long
getUpTime(void)
{
    std::string uptimeSecs;
    unsigned long long res;

    std::ifstream procUptime{"/proc/uptime", std::ios::in};
    if (!procUptime || procUptime.fail())
    {
        std::cerr << "Error opening /proc/utime!" << std::endl;
        throw std::ios::failure("Error opening file!");
    }

    procUptime >> uptimeSecs;

    if (procUptime.fail())
    {
        std::cerr << "Error reading from /proc/utime. No Permission?"
            << std::endl;
        throw std::ios::failure("Error reading from file!");
    }

    std::stringstream{uptimeSecs} >> res;
    return res;
}

//  ..include/proc/misc.h seems to not be present in archlinux
//  this is the procps inplementation.
long
procps_hertz_get(void)
{
    long hz;

#ifdef _SC_CLK_TCK
    if ((hz = sysconf(_SC_CLK_TCK)) > 0)
        return hz;
#endif
#ifdef HZ
    return(HZ);
#endif
    /* Last resort, assume 100 */
    return 100;
}

