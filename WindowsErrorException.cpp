#include "WindowsErrorException.hpp"

#include <sstream>
#include <windows.h>

WindowsErrorException::WindowsErrorException(std::string location, int error_num, std::string error_msg) :
    std::runtime_error(format_message(location, error_num, error_msg)),
    location(location),
    error_num(error_num),
    error_msg(error_msg)
{
}

std::string WindowsErrorException::format_message(std::string location, int error_num, std::string error_msg)
{
    std::stringstream msg;
    msg << "Error: " << location << "\n" << error_num << ": " << error_msg;
    return msg.str();
}

WindowsErrorException WindowsErrorException::FromGetLastError(std::string location)
{
    DWORD error_num = GetLastError();

    LPVOID lpMsgBuf;
    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error_num,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

    std::string error_msg((LPCTSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);
    return WindowsErrorException(location, error_num, error_msg);
}