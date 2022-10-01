#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

void sigint_handler(int signum) {
	// send SIGKILL to all processes in group, so this process and children
	// will terminate.  Use SIGKILL because SIGTERM and SIGINT (among
	// others) are overridden in the child.
	kill(-getpgid(0), SIGKILL);
}

int main(int argc, char *argv[]) {
	char *scenario = argv[1];
	int pid = atoi(argv[2]);

	struct sigaction sigact;

	// Explicitly set flags
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = sigint_handler;
	// Override SIGINT, so that interrupting this process sends SIGKILL to
	// this one and, more importantly, to the child.
	sigaction(SIGINT, &sigact, NULL);

	switch (scenario[0]) {
	case '0': // pass
		kill(pid, SIGHUP);
		sleep(1);
		break;
	case '1': // pass
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		// kill(pid, SIGKILL);
		// sleep(1);
		break;
	case '2': // pass
		kill(pid, SIGHUP);
		sleep(10);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '3': // pass
		kill(pid, SIGHUP);
		sleep(1);
		kill(pid, SIGHUP);
		// sleep(3);
		sleep(8);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '4': // pass
		kill(pid, 12);
		// sleep(1);
		kill(pid, SIGHUP);
		sleep(1);
		kill(pid, SIGINT);
		// sleep(3);
		sleep(8);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '5':
		kill(pid, SIGHUP);
		sleep(1);
		kill(pid, 31);
		sleep(1);
		kill(pid, 10);
		sleep(1);
		// kill(pid, SIGCHLD);
		// // kill(pid, SIGINT);
		// sleep(1);




		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '6': // pass
		kill(pid, SIGHUP); // print 1 and 2
		sleep(5);
		kill(pid, 10); // set foo to 0
		sleep(1);
		kill(pid, 16);
		sleep(1);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '7': // pass
		kill(pid, SIGHUP);
		sleep(5);
		kill(pid, 10);
		sleep(1);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '8': // pass
		kill(pid, 31); // set block to 1
		sleep(1);
		kill(pid, SIGHUP); // print 1 and 2
		sleep(5);
		kill(pid, 10); // set foo to 0
		sleep(1);
		kill(pid, 30); // set foo to 6
		sleep(1);
		kill(pid, SIGTERM); // print foo
		sleep(1);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;
	case '9': 
		kill(pid, SIGQUIT);
		kill(pid, 31);
		sleep(10);
		// kill(pid, SIGINT);
		// sleep(5);
		kill(pid, 12);
		sleep(1);
		kill(pid, SIGTERM);
		break;

	}
	waitpid(pid, NULL, 0);
}
