#include <stdio.h>
#include <sys/statvfs.h>

int main() {
    struct statvfs fs;

    if (statvfs("/", &fs) != 0) {
        perror("statvfs failed");
        return 1;
    }

    unsigned long total = fs.f_blocks * fs.f_frsize;
    unsigned long free = fs.f_bfree * fs.f_frsize;

    printf("Disk Total: %lu bytes\n", total);
    printf("Disk Free : %lu bytes\n", free);
    return 0;
}
