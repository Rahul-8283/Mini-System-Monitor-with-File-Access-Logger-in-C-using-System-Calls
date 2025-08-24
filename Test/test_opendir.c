#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");   // Open /proc directory
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    printf("Listing /proc entries:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);  // Each file/dir name
    }
    closedir(dir);
    return 0;
}
