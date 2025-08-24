#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Before fork: My PID = %d, My Parent PID = %d\n", getpid(), getppid());

    pid = fork();   // create a new process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {

        printf("Child:  My PID = %d, Parent PID = %d\n", getpid(), getppid());  //hild process
    } else {
 
        printf("Parent: My PID = %d, Child PID = %d\n", getpid(), pid);   //parent process
        wait(NULL);  
    }

    return 0;
}
