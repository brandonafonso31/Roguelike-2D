#ifndef PATHS_H
#define PATHS_H

void InitPaths(void);
const char* GetAssetsPath(void);
const char* GetSrcPath(void);
const char* GetConfigPath(void);
const char* GetFontPath(void);

extern const char* list_subfolders[];
extern const char* list_subsubfolders[];
extern const int list_subfolders_count;
extern const int list_subsubfolders_count;
    
#endif