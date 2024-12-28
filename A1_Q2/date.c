#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

//--------------------------------------------------------//
// initialisation and int main
int main(int argc, char *argv[])
{
    int timeshown = 0;
    int formats = 0;
    int yesterdayy = 0;
    int tomorroww = 0;
    int dayafterr = 0;
    int daybeforee = 0;
    char *filename = NULL;
    //--------------------------------------------------------//
    // reading and interpreting arguments inputted on the shell
    // setting variables "timeshown" and "formats" for -d and -r command respectively

    if (argc > 1)
    {
        int index = 1;
        while (index < argc)
        {
            if (strcmp(argv[index], "-d") == 0)
            {
                timeshown = 1;
            }
            else if (strcmp(argv[index], "yesterday") == 0)
            {
                yesterdayy = 1;
            }
            else if (strcmp(argv[index], "tomorrow") == 0)
            {
                tomorroww = 1;
            }
            else if (strcmp(argv[index], "dayafter") == 0)
            {
                dayafterr = 1;
            }
            else if (strcmp(argv[index], "daybefore") == 0)
            {
                daybeforee = 1;
            }
            else if (strcmp(argv[index], "-R") == 0)
                formats = 1;
            else if (strcmp(argv[index], "dir") == 0)
            {
                continue;
            }
            else
            {
                // if the file name is given into the argument itself like "word -n input.txt"
                filename = argv[index];
            }
            index++;
        }
    }

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0)
    {
        printf("Error: Cannot access file %s\n", filename);
        return 1;
    }

    //-----------------------------------------------------------//
    // printing based on given command, whether rfc 5322 or string

    if (timeshown && yesterdayy)
    {
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        tm_info->tm_mday -= 1;
        char printtime[100];

        strftime(printtime, sizeof(printtime), "%a, %d %b %Y %H:%M:%S %z", tm_info);

        printf("Last modified time of %s (RFC 5322 format) : %s\n", filename, printtime);
        // printf("Last modified time of %s : %s", filename, ctime(&file_stat.st_mtime));
    }
    else if (timeshown && tomorroww)
    {
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        tm_info->tm_mday += 1;
        char printtime[100];

        strftime(printtime, sizeof(printtime), "%a, %d %b %Y %H:%M:%S %z", tm_info);

        printf("Last modified time of %s (RFC 5322 format) : %s\n", filename, printtime);
        // printf("Last modified time of %s : %s", filename, ctime(&file_stat.st_mtime));
    }
    else if (timeshown && dayafterr)
    {
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        tm_info->tm_mday += 2;
        char printtime[100];

        strftime(printtime, sizeof(printtime), "%a, %d %b %Y %H:%M:%S %z", tm_info);

        printf("Last modified time of %s (RFC 5322 format) : %s\n", filename, printtime);
        // printf("Last modified time of %s : %s", filename, ctime(&file_stat.st_mtime));
    }
    else if (timeshown && daybeforee)
    {
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        tm_info->tm_mday -= 2;
        char printtime[100];

        strftime(printtime, sizeof(printtime), "%a, %d %b %Y %H:%M:%S %z", tm_info);

        printf("Last modified time of %s (RFC 5322 format) : %s\n", filename, printtime);
        // printf("Last modified time of %s : %s", filename, ctime(&file_stat.st_mtime));
    }
    else if (formats)
    {
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        char printtime[100];

        strftime(printtime, sizeof(printtime), "%a, %d %b %Y %H:%M:%S %z", tm_info);

        printf("Last modified time of %s (RFC 5322 format) : %s\n", filename, printtime);
    }
    else
    {
        printf("Last modified time of %s : %s", filename, ctime(&file_stat.st_mtime));
    }

    return 0;
}
