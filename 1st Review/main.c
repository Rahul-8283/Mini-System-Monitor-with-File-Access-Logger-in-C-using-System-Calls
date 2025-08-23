// menu driven c program

// Listing processes (/proc + opendir() / readdir())
// Killing a process (kill())
// Logging file access (stat())

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>

// Function to list running processes
void list_processes() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("\n%-10s %-20s\n", "PID", "Process");
    printf("---------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char *endptr;
            long pid = strtol(entry->d_name, &endptr, 10);

            if (*endptr == '\0') { // directory name is a number → PID
                char comm_file[256];
                snprintf(comm_file, sizeof(comm_file), "/proc/%ld/comm", pid);

                FILE *fp = fopen(comm_file, "r");
                if (fp) {
                    char name[256];
                    fgets(name, sizeof(name), fp);
                    name[strcspn(name, "\n")] = 0; // remove newline
                    printf("%-10ld %-20s\n", pid, name);
                    fclose(fp);
                }
            }
        }
    }

    closedir(dir);
}

// Function to kill a process by PID
void kill_process() {
    int pid;
    printf("\nEnter PID to kill: ");
    scanf("%d", &pid);

    if (kill(pid, SIGKILL) == 0) {
        printf("Process %d terminated successfully.\n", pid);
    } else {
        perror("kill");
    }
}

// Function to log file access times
void log_file_access() {
    char filename[256];
    struct stat fileStat;

    printf("\nEnter file name: ");
    scanf("%s", filename);

    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Last Access : %s", ctime(&fileStat.st_atime));
    printf("Last Modified : %s", ctime(&fileStat.st_mtime));
    printf("Last Status Change : %s", ctime(&fileStat.st_ctime));
}

// Main menu
int main() {
    int choice;

    while (1) {
        printf("\n===== Mini System Monitor =====\n");
        printf("1. List Active Processes\n");
        printf("2. Kill a Process\n");
        printf("3. Log File Access Times\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: list_processes(); break;
            case 2: kill_process(); break;
            case 3: log_file_access(); break;
            case 0: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
