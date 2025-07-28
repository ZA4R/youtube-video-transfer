#include "functions.h"

// path to specific directory on phone
const char* path = "mtp://SAMSUNG_SAMSUNG_Android_48514e4631423498/Phone/DCIM/YouTube";

// returns pointer to specific directory on phone containing yt content
DIR* open_phone_dir() {
    return opendir(path);
}

/* 
    copies given file to specific destination for use
*/
void copy_to_yt_folder(struct dirent *dir) {
    char file_path[150];

    // snprintf chain length to setup file_path
    int len = 0;
    len = snprintf(file_path, sizeof(file_path), "%s/", path);
    len = snprintf(file_path + len, sizeof(file_path), "%s/", dir->d_name);
    
    // destination directory path
    const char *destination = "/home/dunk/Youtube/current";
    
    FILE *file = fopen(file_path, "r");


    return;
}