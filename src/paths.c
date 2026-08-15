#include "paths.h"

static char assets_path[MAX_PATH_LENGTH] = {0};
static char src_path[MAX_PATH_LENGTH] = {0};
static char config_path[MAX_PATH_LENGTH] = {0};
static char sounds_path[MAX_PATH_LENGTH] = {0};
static char images_path[MAX_PATH_LENGTH] = {0};
static char fonts_path[MAX_PATH_LENGTH] = {0};
static char menu_path[MAX_PATH_LENGTH] = {0};
static int initialized = 0;

const char* list_subfolders[] = {
    "./assets",
    "./src"
};

const char* list_subsubfolders[] = {
    "/config",
    "/sounds", 
    "/images",
    "/fonts"
};

const int listSubfoldersCount = sizeof(list_subfolders) / sizeof(list_subfolders[0]);
const int listSubsubfoldersCount = sizeof(list_subsubfolders) / sizeof(list_subsubfolders[0]);

void InitPaths(void) {
    if (initialized) return;
    
    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, ".");
    }

    // Chemins de base (relatifs)
    snprintf(assets_path, sizeof(assets_path), "%s",list_subfolders [0]);
    snprintf(src_path, sizeof(src_path), "%s", list_subfolders[1]);
    
    snprintf(config_path, sizeof(config_path), "%s%s", assets_path, list_subsubfolders[0]);
    snprintf(sounds_path, sizeof(sounds_path), "%s%s", assets_path, list_subsubfolders[1]);
    snprintf(images_path, sizeof(images_path), "%s%s", assets_path, list_subsubfolders[2]);
    snprintf(fonts_path, sizeof(fonts_path), "%s%s", assets_path, list_subsubfolders[3]);
    snprintf(menu_path, sizeof(menu_path)+sizeof("/menu"), "%s%s", images_path, "/menu");

    printf("Cur rep: %s\n", cwd);
    printf("Assets path: %s\n", assets_path);
    printf("Src path: %s\n", src_path);

    printf("Config path: %s\n", config_path);
    printf("Sounds path: %s\n", sounds_path);
    printf("Images path: %s\n", images_path);
    printf("Font path: %s\n", fonts_path);

    printf("Menu path: %s\n", menu_path);
    
    initialized = 1;
}

const char* getAssetsPath(void) {
    if (!initialized) InitPaths();
    return assets_path;
}

const char* getSrcPath(void) {
    if (!initialized) InitPaths();
    return src_path;
}

const char* getConfigPath(void) {
    if (!initialized) InitPaths();
    return config_path;
}

const char* getFontsPath(void) {
    if (!initialized) InitPaths();
    return fonts_path;
}

const char* getImagesPath(void) {
    if (!initialized) InitPaths();
    return images_path;
}

const char* getSoundsPath(void) {
    if (!initialized) InitPaths();
    return sounds_path;
}

const char* getMenuPath(void) {
    if (!initialized) InitPaths();
    return menu_path;
}