#ifndef PATHS_H
#define PATHS_H

#include <stdio.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#endif

#define MAX_PATH_LENGTH 1024

void InitPaths(void);
const char* getAssetsPath(void);
const char* getSrcPath(void);
const char* getConfigPath(void);
const char* getFontsPath(void);
const char* getImagesPath(void);
const char* getSoundsPath(void);
const char* getMenuPath(void);
const char* getSystemPath(void);

extern const char* lis_subfolders[];
extern const char* list_subsubfolders[];
extern const int listSubfoldersCount;
extern const int listSubsubfoldersCount;
    
#endif