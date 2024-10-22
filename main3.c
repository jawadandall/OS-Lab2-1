#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
    pid_t child1, child2;
    int status;

    // Seed the random number generator with the current time
    srandom(time(NULL));

    printf("Parent Pid: %d, starting the program.\n", getpid());

    // Fork the first child
    child1 = fork();
    
    if (child1 == -1) {
        perror("Failed to fork child1");
        exit(1);
    }

    if (child1 == 0) {
        // Child 1 process
        printf("Child 1 (Pid: %d) created.\n", getpid());
        int iterations = random() % 31;  // Random number of iterations (0-30)
        int i;
        for (i = 0; i < iterations; i++) {
            int sleep_time = random() % 11; // Sleep time (0-10 seconds)
            printf("Child 1 (Pid: %d) is going to sleep for %d seconds!\n", getpid(), sleep_time);
            sleep(sleep_time);
            printf("Child 1 (Pid: %d) is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    } 

    // Fork the second child
    child2 = fork();
    
    if (child2 == -1) {
        perror("Failed to fork child2");
        exit(1);
    }

    if (child2 == 0) {
        // Child 2 process
        printf("Child 2 (Pid: %d) created.\n", getpid());
        int iterations = random() % 31;  // Random number of iterations (0-30)
        int i;
        for (i = 0; i < iterations; i++) {
            int sleep_time = random() % 11; // Sleep time (0-10 seconds)
            printf("Child 2 (Pid: %d) is going to sleep for %d seconds!\n", getpid(), sleep_time);
            sleep(sleep_time);
            printf("Child 2 (Pid: %d) is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    }

    // Parent process
    if (child1 > 0 && child2 > 0) {
        printf("Parent (Pid: %d) is waiting for children to finish.\n", getpid());
        // Wait for both child processes to terminate
        waitpid(child1, &status, 0);
        printf("Child Pid: %d has completed.\n", child1);
        
        waitpid(child2, &status, 0);
        printf("Child Pid: %d has completed.\n", child2);
    }
    
    return 0;
}
