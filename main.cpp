/*
 * @Copyrigt 2023, liserver. All rights reserved.
 * MIT License.
 */

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "token/TokenStream.h"           // TokenStream
#include "tokenAnalysis/TokenAnalysis.h" // TokenAnalysis

#include "core/Compiler.h"

#include "library/console/prints.h"     // Info Warn Error
#include "library/system/rwfile.h"      // ReadWriteFile
#include "library/application/config.h" // Configtion
#include "library/application/args.h"   // ApplicationArguments

int main(int argc, char **argv)
{
    ApplicationArguments args(argc, argv, &Configtion);

#if DEBUG
    Message::Info("System type: " + std::to_string(_OS));
#endif

    for (int i = 0; i < (int)args.TargetFiles.size(); i++)
    {
        std::string TargetFile = args.TargetFiles[i];
        std::string TargetCode = ReadFile(TargetFile);
        TokenSpace::TokenStream TargetCodeTokenStream =
            TokenSpace::ReadString(TargetCode);
        if (TargetCodeTokenStream.Size() == 0)
        {
            Message::Error("File no text", CP_ERR, CP_FINE_NO_TEXT, true);
        }
        if (Configtion.SaveTokenStream)
        {
            std::string temp = "File: " + TargetFile + "\n";
            for (int i = 0; i < TargetCodeTokenStream.Size(); i++)
            {
                TargetCodeTokenStream.Next();
                Token tempT = TargetCodeTokenStream.GetCurToken();
                temp += std::to_string((int)tempT.code) + " " + tempT.value + " " + std::to_string(tempT.line) + "\n";
            }
            temp += "FileEnd: " + TargetFile + "\n";
            WriteFile(Configtion.TokenStreamPath, &temp);
        }
        Parser parser(TargetCodeTokenStream);
        parser.parse();
    }

    return 0; // Return Code 0;
}