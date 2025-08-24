#include <stdio.h>
#include <unistd.h>

int main() {
    char path[256];
    char exe[256];
    ssize_t len;

    snprintf(path, sizeof(path), "/proc/%d/exe", getpid()); // self process
    len = readlink(path, exe, sizeof(exe) - 1);
    if (len == -1) {
        perror("readlink failed");
        return 1;
    }

    exe[len] = '\0';  // Null-terminate
    printf("Executable Path: %s\n", exe);
    return 0;
}
