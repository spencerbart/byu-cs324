#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

    // takes a file name and creates a file pointer.
    FILE *file_pointer;

    file_pointer = fopen(argv[1],"r");
    if (file_pointer == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read contents from file
    char c = fgetc(file_pointer);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(file_pointer);
    }

    fclose(file_pointer);
}