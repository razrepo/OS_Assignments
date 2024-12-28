#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <unistd.h>

int factorial(int n);

void fibonacci(int n);

int main()
{
    printf("Hello (PID:%d)\n", getpid());
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (child_pid == 0)
    {
        wait(NULL);
        printf("I am CHILD (PID:%d)\n", getpid());
        printf("Factorial of 4 :%d\n", factorial(4));
    }
    else
    {
        printf("I am PARENT of %d (PID: %d)\n", child_pid, getpid());
        printf("Fibonacci series up to 16:");
        fibonacci(16);
        printf("\n");

        return 0;
    }
}

void fibonacci(int n)
{
    int fib1 = 0;
    int fib2 = 1;
    printf("%d %d ", fib1, fib2);
    for (int i = 0; i < n - 2; i++)
    {
        int fib3 = fib1 + fib2;
        printf("%d ", fib3);
        fib1 = fib2;
        fib2 = fib3;
    }
}

int factorial(int n)
{
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}
