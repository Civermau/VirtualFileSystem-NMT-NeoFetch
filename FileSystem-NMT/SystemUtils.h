#include <iostream>

#ifdef __linux__
    #include <unistd.h>
    #include <pwd.h>
    #include <sys/types.h>
    #include <sys/utsname.h>
    #include <sys/utsname.h>
#elif _WIN32
    #include <windows.h>
#endif

namespace sys {
    std::string getUsername();
    std::string getHostname();
    std::string getKernelVersion();
    void test();
}
