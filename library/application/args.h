#define DISABLE_PLATFORM_H
#include "core/Compiler.h"

#include <iostream>
#include <string>
#include <vector>

#include "library/console/prints.h"
#include "library/system/rwfile.h"
#include "config.h"

#ifndef __ARGS_H__
#define __ARGS_H__

class ApplicationArguments
{
public:
    int argc;
    char **argv;
    __Configtion *Configtion;
    std::vector<std::string> TargetFiles;
    ApplicationArguments(){};
    ApplicationArguments(int argc, char **argv, __Configtion *Configtion)
    {
        this->argc = argc;
        this->argv = argv;
        this->Configtion = Configtion;
        this->Pause();
    }

    void __Pause() // Pause File
    {
        for (int i = 0; i < (int)this->TargetFiles.size(); i++)
        {
            if (!std::ifstream(this->TargetFiles[i]))
                Message::Error("File " + TargetFiles[i] + " not found.", CP_ERR, CP_FILE_NOT_FOUND, true);
        }
    }

    void Pause()
    {
        if (this->argc < 2)
        {
            Message::Error("No any args.", 0, 1, true);
        }

        int i = 1;         // i always point to the current argv
        char *f = nullptr; // f always point to the next argv

        while (i < this->argc)
        {
            f = argv[i + 1]; // set f to the next argv
            if (i == this->argc - 1 || f == nullptr)
            {
                if (argv[i][0] == '-')
                    Message::Error("Argument must not be end.", CP_ERR, CP_ARG_MUST_NOT_END, true);
                else
                    TargetFiles.push_back(argv[i]);
            }
            else if (argv[i][0] == '-')
            {
                // Arguments
                if (0 == strcmp(argv[i], "-SC"))
                {
                    // Save the TokenStream to file (Next argv must be file path)
                    if (f[0] == '-')
                        Message::Error("Argument must not be end.", CP_ERR, CP_ARG_MUST_NOT_END, true);
                    else
                    {
                        ReadFile(f); // Is file exist?
                        // Change the Configtion
                        this->Configtion->SaveTokenStream = true;
                        this->Configtion->TokenStreamPath = f;
                    }
                    i += 2;
                }
                else if (0 == strcmp(argv[1], "-O"))
                    this->Configtion->TargetFileName = f;
            }
            else
                TargetFiles.push_back(argv[i]);

            i++;
            f = NULL;
        }
        this->__Pause();
    }
};

#endif // !__ARGS_H__