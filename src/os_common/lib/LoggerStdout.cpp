#include "LoggerStdout.h"

#include <iostream>

namespace omni
{
//private
//protected
//public
    LoggerStdout::~LoggerStdout()
    {

    }

    Logger& LoggerStdout::operator<< (bool val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (short val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (unsigned short val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (int val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (unsigned int val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (long val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (unsigned long val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (float val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (double val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (long double val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (void* val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (const char* val)
    {
        std::cout << val;
        return *this;
    }

    Logger& LoggerStdout::operator<< (char val)
    {
        std::cout << val;
        return *this;
    }
}
