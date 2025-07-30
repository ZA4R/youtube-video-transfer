#include "functions.h"

int main(void) {
    DIR *d;
    d = open_phone_dir();

    if (!d) {
        printf("Phone directory retrival unsuccessful\n");
        return 1;
    }

    return 0;
    // points to each individual file as it loops through dir
    struct dirent *dir;

    while ((dir = readdir(d)) != NULL) copy_to_yt_folder(dir);
    
    closedir(d);
    return 0;
}