#include "il2cpp-config.h"
#include "il2cpp-vm-support.h"

#if !IL2CPP_USE_GENERIC_ENVIRONMENT && IL2CPP_TARGET_POSIX && !IL2CPP_TARGET_PS4
#include "il2cpp-class-internals.h"
#include "os/Environment.h"
#include "il2cpp-api.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

#if defined(__APPLE__) && !defined(__arm__)
// Apple defines this in crt_externs.h but doesn't provide that header for
// arm-apple-darwin9.  We'll manually define the symbol on Apple as it does
// in fact exist on all implementations (so far)
extern "C" char*** _NSGetEnviron(void);
#define environ (*_NSGetEnviron())
#else
extern char **environ; // GNU C library
#endif

namespace il2cpp
{
namespace os
{
    std::string Environment::GetMachineName()
    {
        char buf[256];

        if (gethostname(buf, sizeof(buf)) != 0)
            return NULL;

        return buf;
    }

    int32_t Environment::GetProcessorCount()
    {
        int count = 1;
#ifdef _SC_NPROCESSORS_ONLN
        count = (int)sysconf(_SC_NPROCESSORS_ONLN);
        if (count > 0)
            return count;
#endif
#ifdef USE_SYSCTL
        {
            int mib[2];
            size_t len = sizeof(int);
            mib[0] = CTL_HW;
            mib[1] = HW_NCPU;
            if (sysctl(mib, 2, &count, &len, NULL, 0) == 0)
                return count;
        }
#endif
        return count;
    }

    std::string Environment::GetOsVersionString()
    {
        struct utsname name;

        if (uname(&name) >= 0)
            return name.release;

        return "0.0.0.0";
    }

    std::string Environment::GetOsUserName()
    {
        const std::string username(GetEnvironmentVariable("USER"));
        return username.empty() ? "Unknown" : username;
    }

    std::string Environment::GetEnvironmentVariable(const std::string& name)
    {
        const char* variable = getenv(name.c_str());
        return variable ? std::string(variable) : std::string();
    }

    void Environment::SetEnvironmentVariable(const std::string& name, const std::string& value)
    {
        if (value.empty())
        {
            unsetenv(name.c_str());
        }
        else
        {
            setenv(name.c_str(), value.c_str(), 1); // 1 means overwrite
        }
    }

    std::vector<std::string> Environment::GetEnvironmentVariableNames()
    {
        std::vector<std::string> result;

        for (char **envvar = environ; *envvar != NULL; ++envvar)
        {
            const char* equalAddress = strchr(*envvar, '=');

            if (equalAddress != NULL)
                result.push_back(std::string(*envvar, size_t(equalAddress - *envvar)));
        }

        return result;
    }

    std::string Environment::GetHomeDirectory()
    {
        static std::string homeDirectory;

        if (!homeDirectory.empty())
            return homeDirectory;

        homeDirectory = GetEnvironmentVariable("HOME");

        return homeDirectory.empty() ? "/" : homeDirectory;
    }

    std::vector<std::string> Environment::GetLogicalDrives()
    {
        std::vector<std::string> result;

        // This implementation is not correct according to the definition of this icall, but this is
        // the only "logical drive" that the Mono version in Unity returns for OSX.
        result.push_back("/");

        // TODO: Implement additional logic for Linux

        return result;
    }

    void Environment::Exit(int result)
    {
        IL2CPP_VM_SHUTDOWN();
        exit(result);
    }

    NORETURN void Environment::Abort()
    {
        abort();
    }

    std::string Environment::GetWindowsFolderPath(int folder)
    {
        // This should only be called on Windows.
        return std::string();
    }

#if NET_4_0

    bool Environment::Is64BitOs()
    {
        struct utsname name;

        if (uname(&name) >= 0)
        {
            return strcmp(name.machine, "x86_64") == 0 || strncmp(name.machine, "aarch64", 7) == 0 || strncmp(name.machine, "ppc64", 5) == 0;
        }

        return false;
    }

#endif
}
}
#endif
