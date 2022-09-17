#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
	int pid;
	FILE * the_file;
	int pipe_file[2];

	printf("Starting program; process has pid %d\n", getpid());
	the_file = fopen("fork-output.txt", "w+");

	fprintf(the_file, "%s", "BEFORE FORK\n");
	fflush(the_file);

	pipe(pipe_file);

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */

	printf("Section A;  pid %d\n", getpid());
	fprintf(the_file, "%s", "SECTION A\n");
	fflush(the_file);
	// sleep(30);

	/* END SECTION A */
	if (pid == 0) {
		/* BEGIN SECTION B */
		
		printf("Section B; pid %d\n", getpid());

		close(pipe_file[0]);
		FILE * fd_one = fdopen(pipe_file[1],"w");
		fputs( "hello from Section B\n", fd_one);

		fprintf(the_file, "%s", "SECTION B\n");
		fflush(the_file);
		// sleep(30);
		// sleep(30);
		// printf("Section B done sleeping\n");

		//////////////////////////////////////////
		char *newenviron[] = { NULL };

		printf("Program \"%s\" has pid %d. Sleeping.\n", argv[0], getpid());
		// sleep(30);

		if (argc <= 1) {
			printf("No program to exec.  Exiting...\n");
			exit(0);
		}

		printf("Running exec of \"%s\"\n", argv[1]);
		int file_descriptor = fileno(the_file);
		dup2(fileno(the_file), 1);
		execve(argv[1], &argv[1], newenviron);
		printf("End of program \"%s\".\n", argv[0]);
		/////////////////////////////////////////

		exit(0);

		/* END SECTION B */
	} else {
		/* BEGIN SECTION C */
		wait(NULL);
		printf("Section C\n");

		close(pipe_file[1]);
		FILE * fd;
		fd = fdopen(pipe_file[0],"r");
		char buf[100];
		fgets(buf,100,fd);
		fputs(buf,stdout); 

		fprintf(the_file, "%s", "SECTION C\n");
		fflush(the_file);


		// sleep(30);
		// printf("Section C done sleeping\n");

		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */

	printf("Section D\n");
	fprintf(the_file, "%s", "SECTION D\n");
	fflush(the_file);
	sleep(30);

	/* END SECTION D */
}

