#ifndef PATHS_H
#define PATHS_H

#include <stdio.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#endif

#define MAX_PATH_LENGTH 1024

void InitPaths(void);
const char* GetAssetsPath(void);
const char* GetSrcPath(void);
const char* GetConfigPath(void);
const char* GetFontsPath(void);
const char* GetImagesPath(void);
const char* GetSoundsPath(void);

extern const char* lis_subfolders[];
extern const char* list_subsubfolders[];
extern const int listSubfoldersCount;
extern const int listSubsubfoldersCount;
    
#endif