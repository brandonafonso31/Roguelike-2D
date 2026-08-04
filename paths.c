#include "paths.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#endif

static char assets_path[1024] = {0};
static char src_path[1024] = {0};
static int initialized = 0;

void InitPaths(void) {
    if (initialized) return;
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, ".");
    }
    
    if (assets_path[0] == '\0') {
        snprintf(assets_path, sizeof(assets_path), "./assets");
    }
    
    // Chemin vers src (généralement le même niveau que assets)
    snprintf(src_path, sizeof(src_path), "./src");
    
    printf("Assets path: %s\n", assets_path);
    printf("Src path: %s\n", src_path);
    
    initialized = 1;
}

const char* GetAssetsPath(void) {
    if (!initialized) InitPaths();
    return assets_path;
}

const char* GetSrcPath(void) {
    if (!initialized) InitPaths();
    return src_path;
}