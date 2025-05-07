#include "SystemUtils.h"

namespace sys {
    #ifdef __linux__
    std::string getUsername() {
        struct passwd *pw = getpwuid(getuid());
        return pw ? pw->pw_name : "Unknown";
    }

    std::string getHostname() {
        char buffer[256];
        if (gethostname(buffer, sizeof(buffer)) == 0) {
            return std::string(buffer);
        }
        return "Unknown";
    }

    std::string getKernelVersion() {
        struct utsname u;
        uname(&u);
        return std::string(u.sysname) + " " + u.release;
    }

    void test() {
        std::cout << "Test on Linux" << std::endl;
    }

    #elif _WIN32
    std::string getUsername() {
        return "Unknown";
    }

    std::string getHostname() {
        return "Unknown";
    }

    std::string getKernelVersion() {
        return "Unknown";
    }
    
    void test() {
        std::cout << "Test on Windows" << std::endl;
    }
    #endif
} 