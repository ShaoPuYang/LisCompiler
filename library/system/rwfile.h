#include <iostream>
#include <vector>

#include <string>
#include <string.h>

#include <fstream>

#include "core/Compiler.h"
#include "token/TokenStream.h"

#include "library/console/prints.h"

// Read file with file path
std::string ReadFile(std::string FilePath);

void WriteFile(std::string filepath, std::string *Str);