#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat fileStat;

    if (stat("test.txt", &fileStat) == -1) {
        perror("stat failed");
        return 1;
    }

    printf("File Size: %ld bytes\n", fileStat.st_size);
    printf("Last Access: %ld\n", fileStat.st_atime);
    printf("Permissions: %o\n", fileStat.st_mode & 0777);
    return 0;
}

// #include <stdio.h>
// #include <sys/stat.h>
// #include <time.h>

// int main() {
//     struct stat fileStat;

//     if (stat("test.txt", &fileStat) == -1) {
//         perror("stat failed");
//         return 1;
//     }

//     printf("File Size: %ld bytes\n", fileStat.st_size);
//     printf("Last Access: %s", ctime(&fileStat.st_atime)); // formatted
//     printf("Last Modified: %s", ctime(&fileStat.st_mtime));
//     printf("Last Status Change: %s", ctime(&fileStat.st_ctime));

//     return 0;
// }

