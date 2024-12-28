#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "word.c"
// word is imported to be used an an internal command like in the parent process
//----------------------------------------------------------------//
// command function that forks the parent process and executes given command externally

void command(char *command)
{
    //-------------------------------//
    // reads splits and interprets command given in the shell
    char *args[256];
    int argc = 0;
    char *token = strtok(command, " \t\n");

    while (token != NULL)
    {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[argc] = NULL;

    //----------------------------------------------------//
    // if the given command is word, it is executed by directly calling "int word()" from its file

    if (strcmp(args[0], "word") == 0)
    {
        word(argc, args);
    }
    //----------------------------------------------------//
    // if the dir command is called, the parent process is forked and the dir command is executed

    else if (strcmp(args[0], "dir") == 0)
    {
        pid_t dirPro = fork();
        if (dirPro == -1)
        {
            perror("fork");
        }
        else if (dirPro == 0)
        {
            // execl to pin point every element of the written command "dir -r abcd"
            execl("./dir", "dir", args[0], args[1], args[2], NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }

    //----------------------------------------------------//
    // if the date command is called, the parent process is forked and the date command is executed

    else if (strcmp(args[0], "date") == 0)
    {
        pid_t datePro = fork();
        if (datePro == -1)
        {
            perror("fork");
        }
        else if (datePro == 0)
        {
            // similar to how dir was called, date is called and arguments are read separately
            execl("./date", "date", args[0], args[1], args[2], NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
        // original paretn process that waits until one of the commands are executed to run it again
        else
        {
            wait(NULL);
        }
    }
}
//--------------------------------------------------------//
// main function to start the shell inside the terminal
// infinite loop to continuously take in commands
//"exit" input to stop the loop and exit the shell back to the terminal
int main()
{
    char input[256];

    char cwd[256];

    while (1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("Shell %s/>> ", cwd);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        command(input);
    }
    return 0;
}