#include "rwfile.h"

std::string ReadFile(std::string FilePath)
{
    // Windows API || Unix API
#if defined(__WIN)
    // Use windows api
    HANDLE hFile = CreateFileA(FilePath.c_str(), GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        Message::Error("File not found.", CP_ERR, CP_FILE_NOT_FOUND, true);
    }
    DWORD dwFileSize = GetFileSize(hFile, NULL);
    char *lpBuffer = (char *)malloc(dwFileSize + 1);
    DWORD dwReadSize = 0;
    ReadFile(hFile, lpBuffer, dwFileSize, &dwReadSize, NULL);
    lpBuffer[dwFileSize] = '\0';
    CloseHandle(hFile);
    return std::string(lpBuffer);

#else
    // Macos or Linux use stdio
    FILE *fp = fopen(FilePath.c_str(), "r");
    if (fp == NULL)
    {
        Message::Error("File not found.", CP_ERR, CP_FILE_NOT_FOUND, true);
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = (char *)malloc(size + 1);
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    fclose(fp);

    return std::string(buffer);

#endif

    return "";
}

void WriteFile(std::string filepath, std::string *Str)
{
#if defined(__WIN)
    // Windows API
    HANDLE hFile = CreateFileA(filepath.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
                               NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        Message::Error("File not found.", CP_ERR, CP_FILE_NOT_FOUND, true);
    }
    DWORD dwWriteSize = 0;
    WriteFile(hFile, Str->c_str(), Str->size(), &dwWriteSize, NULL);
    CloseHandle(hFile);
#else
    // Macos or Linux use stdio
    FILE *fp = fopen(filepath.c_str(), "w");
    if (fp == NULL)
    {
        Message::Error("File not found.", CP_ERR, CP_FILE_NOT_FOUND, true);
    }
    fwrite(Str->c_str(), Str->size(), 1, fp);
    fclose(fp);
#endif
}
