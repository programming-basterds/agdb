#ifndef _MI_UTILS_H_
#define _MI_UTILS_H_

#include <sys/types.h>
#include <signal.h>
#include <regex>
#include "exceptions.h"
#include "mi_gdb.h"

namespace NSCommon
{

static auto PROCESS_REGEX = std::regex("^process (\\d+)$");

inline pid_t getProcessPid(mi_h* handler)
{
    pid_t pid = -1;
    mili::assert_throw<ErrorRequestingThreadInfo>(mi_send(handler, "-thread-info\n"));
    const auto* results = mi_res_done_var(handler, "threads");
    mili::assert_throw<ErrorRequestingThreadInfo>(results != nullptr);
    const auto container = results->v.rs;
    mili::assert_throw<ErrorRequestingThreadInfo>(container != nullptr);
    auto value = container->v.rs;
    while(value != nullptr && std::string(value->var) != "target-id")
        value = value->next;
    if (value != nullptr)
    {
        std::string target = value->v.cstr;
        std::smatch sm;
        std::regex_match(target, sm, PROCESS_REGEX);
        pid = mili::from_string<pid_t>(sm[1u]);
    }
    return pid;
}

inline bool interrupt(pid_t pid)
{
    return kill(pid, SIGINT) != 0;
}

} // namespace NSCommon

#endif // _MI_UTILS_H_
