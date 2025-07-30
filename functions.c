#include "functions.h"
#include <stdlib.h>
#define BUFFER_SIZE (1024 * 1024) // 1 MB

// path to specific directory on phone
const char* path = "mtp://SAMSUNG_SAMSUNG_Android_48514e4631423498/Phone/DCIM/YouTube";

// returns pointer to specific directory on phone containing yt content
DIR* open_phone_dir() {
    return opendir(path);
}

// copies given file to destination
// DOES NOT CLOSE FILE
int copy_file(FILE* to_copy, FILE* destination) {
    if (to_copy == NULL) {
        printf("No file provided to copy\n");
        return 1;
    }
    if (destination == NULL) {
        printf("No destination providied\n");
        return 1;
    }

    char* buffer = (char *)malloc(BUFFER_SIZE);
    size_t bytes_read = 0;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, to_copy)) > 0) {
        if ((fwrite(buffer, 1, bytes_read, destination)) != bytes_read) {
            free(buffer);
            return 2;
        }
    }

    free(buffer);
    return 0;
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
    char destination_path[150];
    const char *destination_dir = "/home/dunk/Youtube/current";

    int len2 = 0;
    len2 = snprintf(destination_path, sizeof(destination_path), "%s/", destination_dir);
    len2 = snprintf(destination_path + len2, sizeof(destination_path), "%s/", dir->d_name);

    
    // open file to be copied
    FILE *file_to_copy = fopen(file_path, "r");

    // open destination file
    FILE *file_destination = fopen(destination_path, "w");

    int return_code = 0;
    return_code = copy_file(file_to_copy, file_destination);

    fclose(file_to_copy);
    fclose(file_destination);

    if (return_code == 2) {
        printf("Unsuccessful write to %s\n", destination_path);
    }

    return;
}