#pragma once

#include <string>
#include <stdexcept>

class WindowsErrorException : public std::runtime_error
{
private:
    std::string location;
    int error_num;
    std::string error_msg;

    static std::string format_message(std::string location, int error_num, std::string error_msg);

public:
    WindowsErrorException(std::string location, int error_num, std::string error_msg);
    static WindowsErrorException FromGetLastError(std::string location);
};


