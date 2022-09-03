//  1. What are the numbers associated with the manual sections for executable
//     programs, system calls, and library calls, respectively?
    
//     Executable programs or `1`
    
//     System calls `2`
    
//     Library calls `3`

//  2. Which section number(s) contain a man page for `kill`?

//     `12`

//  3. Which section number(s) contain a man page for `exit`?

//     `3`

//     `2`

//  4. Which section number(s) contain a man page for `open`?

//     `2`

//  5. What three `#include` lines should be included to use the `open()` system
//     call?

//     ```C
//        #include <sys/types.h>
//        #include <sys/stat.h>
//        #include <fcntl.h>
//     ```
//  6. Which section number(s) contain a man page for `socket`?

//     `7`

//     `2`

//  7. Which `socket` option "Returns a value indicating whether or not this
//     socket has been marked to accept connections with `listen(2)`"?

//     `SO_ACCEPTCONN`

//  8. How many man pages (in any section) contain keyword references to
//     `getaddrinfo`?

//     `3`

//  9. According to the "DESCRIPTION" section of the man page for `string`, the
//     functions described in that man page are used to perform operations on
//     strings that are ________________. (fill in the blank)

//     `null-terminated strings`

//  10. What is the return value of `strcmp()` if the value of its first argument
//      (i.e., `s1`) is _greater than_ the value of its second argument (i.e.,
//      `s2`)?

//      `>0`

// I completed the TMUX exercise from Part 2

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

    if( argc == 2 ) {
    }
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("One argument expected.\n");
    }

    // grab env
    char pattern[BUFSIZE];
    char *envvar = "CATMATCH_PATTERN";
    int envIsPresent = 1;

    // Make sure envar actually exists
    if(!getenv(envvar)){
        // fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        // exit(1);
        envIsPresent = 0;
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

        if (count > 0) 
        {
            count = 1;
        }
        if (!envIsPresent) {
            count = 0;
        }

        printf("%d %s", count, line);
    }

    fclose(file_pointer);
}