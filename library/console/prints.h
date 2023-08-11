// Copyright 2023, liserver. All rights reserved.

#include "token/TokenStream.h"

#define CASE_STR(x) case x : return #x; break;

#ifndef __PRINTS_H__
#define __PRINTS_H__

namespace Message
{
    /*
     * The Message is info message ;
     */
    void Info(std::string Message);

    /*
     * The Message is warning message ;
     * The ExitApplication is exit application or not.
     */
    void Warn(std::string Message, bool ExitApplication);

    /*
     * The Message is error message ;
     * The CompilerCode is code of compiler : eg, 0 is TokenStream, cout TK
     * The ErrorType is type of error : eg, TK0001 is not defined token.
     * The ExitApplication is exit application or not.
     */
    void Error(std::string Message, int CompilerType, int ErrorType, bool ExitApplication);
};

#endif