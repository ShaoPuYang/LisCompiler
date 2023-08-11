#include <iostream>
#include <string>

#ifndef __CONFIG_H__
#define __CONFIG_H__

class __Configtion
{
public:
    // About TokenStream
    bool SaveTokenStream        = false;
    std::string TokenStreamPath = "TokenStream.txt";
    std::string TargetFileName  = "a";  
};

#endif // __CONFIG_H__