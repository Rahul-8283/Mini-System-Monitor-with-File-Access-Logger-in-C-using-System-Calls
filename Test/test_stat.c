#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat fileStat;

    if (stat("test.txt", &fileStat) == -1){
        perror("stat failed");
        return 1;
    }

    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Last Access: %ld\n", fileStat.st_atime);
    printf("Last Modified: %ld\n", fileStat.st_mtime);

    return 0;
}
