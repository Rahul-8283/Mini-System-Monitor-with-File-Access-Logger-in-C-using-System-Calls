#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define STAT_PATH "/proc"

// Function to calculate CPU usage from /proc/[pid]/stat
void show_cpu_usage() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(STAT_PATH);
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("%-10s %-20s %-10s\n", "PID", "Process", "CPU Time");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char *endptr;
            long pid = strtol(entry->d_name, &endptr, 10);

            // Only consider directories that are numbers (process IDs)
            if (*endptr == '\0') {
                char stat_file[256];
                snprintf(stat_file, sizeof(stat_file), "/proc/%ld/stat", pid);

                FILE *fp = fopen(stat_file, "r");
                if (fp) {
                    char comm[256];
                    char state;
                    unsigned long utime, stime;

                    // /proc/[pid]/stat has many fields, we only extract a few
                    fscanf(fp, "%*d (%[^)]) %c", comm, &state); // process name and state
                    for (int i = 0; i < 11; i++) fscanf(fp, "%*s"); // skip unused fields

                    fscanf(fp, "%lu %lu", &utime, &stime); // user time, system time
                    fclose(fp);

                    unsigned long total_time = utime + stime;

                    printf("%-10ld %-20s %-10lu\n", pid, comm, total_time);
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    printf("CPU Usage Per Process:\n");
    show_cpu_usage();
    return 0;
}
