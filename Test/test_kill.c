#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int pid;
    printf("Enter PID to kill: ");
    scanf("%d", &pid);

    if (kill(pid, SIGKILL) == 0) {  
        printf("Process %d killed.\n", pid);
    } 
    else {
        perror("kill failed");
    }
    return 0;
}
