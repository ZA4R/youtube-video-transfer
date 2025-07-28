#include <stdio.h>
#include <string.h>
#include <dirent.h>

// points to each individual file as it loops through dir
    struct dirent;

DIR* open_phone_dir();

void copy_to_yt_folder(struct dirent *dir);