#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    printf("A) Parent (P) is having ID %d\n", getpid());

    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (child_pid == 0)
    {

        printf("C) Child is having ID %d\n", getpid());
        printf("D) My Parent ID is %d\n", getppid());
    }
    else
    {
        wait(NULL);

        printf("B) ID of P's Child is %d\n", child_pid);

        return 0;
    }
}
