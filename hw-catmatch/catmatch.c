#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 80
#define MAX_LINE_LENGTH 1000

void main(int argc, char *argv[])
{
    // get and print the process id to stderr
    __pid_t process_id = getpid();
    fprintf(stderr, "%d\n\n", process_id);

    // if( argc == 2 ) {
    //     printf("The argument supplied is %s\n", argv[1]);
    // }
    // else if( argc > 2 ) {
    //     printf("Too many arguments supplied.\n");
    // }
    // else {
    //     printf("One argument expected.\n");
    // }

    // grab env
    char pattern[BUFSIZE];
    char *envvar = "CATMATCH_PATTERN";

    // Make sure envar actually exists
    if(!getenv(envvar)){
        fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        exit(1);
    }

    // Make sure the buffer is large enough to hold the environment variable
    // value. 
    if(snprintf(pattern, BUFSIZE, "%s", getenv(envvar)) >= BUFSIZE){
        fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", BUFSIZE);
        exit(1);
    }
    // printf("pattern: %s\n", pattern);

    // takes a file name and creates a file pointer.
    FILE *file_pointer;

    file_pointer = fopen(argv[1],"r");
    if (file_pointer == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read contents from file
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file_pointer))
    {
        int count = 0;
        // loop through line and count how many times it matches pattern
        for (size_t i = 0; i < strlen(line); i++)
        {
            int char_count = 0;
            for (size_t j = 0; j < strlen(pattern); j++)
            {
                if (line[i+j] == pattern[j])
                {
                    char_count++;
                }
            }
            if (char_count == strlen(pattern))
            {
                count++;
            }
            
        }

        printf("%d %s", count, line);
    }

    fclose(file_pointer);
}