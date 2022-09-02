#include <stdio.h>
#include <unistd.h>

void main()
{
    // get and print the process id to stderr
    __pid_t process_id = getpid();
    fprintf(stderr, "%d\n\n", process_id);

    // takes a file name and creates a file pointer.
    FILE *file_pointer;

    file_pointer = fopen("fileopen","r");

    fclose(file_pointer);
}