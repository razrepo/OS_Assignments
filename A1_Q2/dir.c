#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

//------------------------------------------------------//

int main(int argc, char *argv[])
{

    char *dirname = NULL;

    int rcommand = 0; // for -r command
    int vcommand = 0; // for -v command

    //------------------------------------------------------//
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-r") == 0)
            {
                rcommand = 1;
            }
            else if (strcmp(argv[i], "-v") == 0)
            {
                vcommand = 1;
            }
            else
            {
                // Assuming the argument is the directory name
                dirname = argv[i];
            }
        }
    }
    //------------------------------------------------------//
    // -r command
    struct stat fileinfo;

    if (stat(dirname, &fileinfo) == 0)
    {
        if (S_ISDIR(fileinfo.st_mode))
        {
            if (rcommand)
            {
                chdir(dirname);
                if (rmdir(dirname) != 0)
                {
                    perror("Error removing existing directory");
                    return 1;
                }
                printf("Removed existing directory: %s\n", dirname);
            }
            else
            {
                chdir(dirname);
                printf("Error: Directory %s already exists.\n", dirname);
                return 1;
            }
        }
        else
        {
            printf("Error: %s is not a directory.\n", dirname);
            return 1;
        }
    }
    //------------------------------------------------------//
    // Create directory
    // handled permissions using 0777
    // -v command

    if (mkdir(dirname, 0777) != 0)
    {
        perror("Error creating directory");
        return 1;
    }

    if (vcommand)
    {
        printf("Directory created: %s\n", dirname);
        chdir(dirname);
        if (chdir(dirname) != 0)
        {
            perror("Failed to change current directory");
            return 1;
        }
        printf("Current directory changed to: %s\n", dirname);
    }

    return 0;
}
