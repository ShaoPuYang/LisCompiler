#include "prints.h"

void Message::Info(std::string Message)
{
    std::cout << "[INFO] " << Message << std::endl;
}

void Message::Warn(std::string Message, bool ExitApplication = false)
{
    // Set color to yellow
    std::cout << "\033[33m" << "[WARN] " << Message << "\033[0m" << std::endl;
    if (ExitApplication)
    {
        exit(0);
    }
}

void Message::Error(std::string Message, int CompilerType, int ErrorType, bool ExitApplication = false)
{
    // Set color to red
    std::cout << "\033[31m";
    switch (CompilerType)
    {
        case 0:
            std::cout << "[ERROR] CP";
            break;
        case 1:
            std::cout << "[ERROR] LK";
        default:
            break;
    }
    std::string ErrorTypeStr = std::to_string(ErrorType);
    while (ErrorTypeStr.length() < 4)
    {
        ErrorTypeStr = "0" + ErrorTypeStr;
    }
    std::cout << "\033[31m" << ErrorTypeStr << ": " << Message << "\033[0m" << std::endl;
    if (ExitApplication)
    {
        exit(0);
    }
}