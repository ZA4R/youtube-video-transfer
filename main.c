#include "functions.h"

int main(void) {
    DIR *d;
    d = open_phone_dir();

    if (!d) {
        perror("Phone directory retrival unsuccessful");
    }

    // points to each individual file as it loops through dir
    struct dirent *dir;

    while ((dir = readdir(d)) != NULL) {
        copy_to_yt_folder(dir);
        closedir(d);
    }

    closedir(d);
    return 0;
}