#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat fileStat;

    if (stat("test.txt", &fileStat) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("Last Modification Time: %s", ctime(&fileStat.st_mtime));
    return 0;
}
