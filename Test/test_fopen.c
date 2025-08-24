// #include <stdio.h>

// int main() {
//     FILE *fp;
//     char buffer[256];

//     fp = fopen("/proc/cpuinfo", "r");   // Open virtual file
//     if (fp == NULL) {
//         perror("fopen failed");
//         return 1;
//     }

//     printf("CPU Info (first line):\n");
//     if (fgets(buffer, sizeof(buffer), fp) != NULL) {
//         printf("%s", buffer);
//     }
//     fclose(fp);
//     return 0;
// }

#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[256];

    fp = fopen("/proc/cpuinfo", "r");   // Open virtual file
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    printf("CPU Info (all lines):\n");

    // Keep reading until EOF
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0;
}

