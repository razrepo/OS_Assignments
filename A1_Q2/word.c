#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word(int argc, char *argv[])
{
    //----------------------------------------------\\
    //initialising variables and switches
    int ignnewline = 0;
    int compare = 0;
    char *f1 = NULL;
    char *f2 = NULL;
    int fcount1 = 0;
    int fcount2 = 0;
    char buffer[1024];

    //----------------------------------------------\\
    // reading and interpreting commands from command line
    if (argc > 1)
    {
        int index = 1;
        while (index < argc)
        {
            if (strcmp(argv[index], "-n") == 0)
                ignnewline = 1;
            else if (strcmp(argv[index], "-d") == 0)
                compare = 1;
            else
            {
                // if the file name is given into the argument itself like "word -n input.txt"
                if (f1 == NULL)
                    f1 = argv[index];
                else if (f2 == NULL)
                    f2 = argv[index];
                else
                {
                    printf("Error: Too many arguments.\n");
                    return 1;
                }
            }
            index++;
        }
    }

    // verify if the command has exactly enough parameters as required by the said command
    //  "3" (3-1 = 2) for -n and "4" (4-1 = 3) for -d

    if ((argc - ignnewline - compare != 2) && (argc - ignnewline - compare != 3))
    {
        printf("Command Syntax: word [-n] [-d] [file1] [file2]\n");
        return 1;
    }

    if (f1 != NULL)
    {
        FILE *file1 = fopen(f1, "r");
        if (file1 == NULL)
        {
            printf("Error: Cannot open file %s\n", f1);
            return 1;
        }
        // loop to read file line by line and give number of words also set "in_word"
        //  if newline character is encountered
        while (fgets(buffer, sizeof(buffer), file1) != NULL)
        {
            int in_word = 0;
            for (int i = 0; buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                    in_word = 0;
                else if (!in_word)
                {
                    fcount1++;
                    in_word = 1;
                }
            }
            if (!ignnewline)
                fcount1++;
        }
        fclose(file1);
    }

    if (f2 != NULL)
    {
        FILE *file2 = fopen(f2, "r");
        if (file2 == NULL)
        {
            printf("Error: File %s inaccessible\n", f2);
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), file2) != NULL)
        {
            // Count words in the line
            int in_word = 0;
            for (int i = 0; buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                    in_word = 0;
                else if (!in_word)
                {
                    fcount2++;
                    in_word = 1;
                }
            }

            if (!ignnewline)
                fcount2++;
        }

        fclose(file2);
    }

    // for the "-d" command: prints the different between two files as the
    //  absolute difference to eliminate sign issues
    if (compare)
    {
        if (f1 != NULL && f2 != NULL)
        {
            int diff = abs(fcount1 - fcount2);
            printf("Difference in word counts between %s and %s: %d\n", f1, f2, diff);
        }
        else
        {
            printf("Error: Two filenames are required for difference\n");
            return 1;
        }
    }
    else
    {
        if (f1 != NULL)
            printf("Word count in %s: %d\n", f1, fcount1);
        if (f2 != NULL)
            printf("Word count in %s: %d\n", f2, fcount2);
    }
    return 0;
}
