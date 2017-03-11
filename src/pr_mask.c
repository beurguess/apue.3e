#include <apue.h>
#include <errno.h>

void pr_mask (const char *str)
{
	sigset_t	sigset;
	int		errno_save;

	errno_save = errno;
	if (sigprocmask (0, NULL, &sigset) < 0)
		err_sys ("setprocmask error");
	else
	{
		printf ("%s", str);
		if (sigismember (&sigset, SIGHUP))
			printf (" SIGHUP");
		if (sigismember (&sigset, SIGINT))
			printf (" SIGINT");
		if (sigismember (&sigset, SIGQUIT))
			printf (" SIGQUIT");
		if (sigismember (&sigset, SIGILL))
			printf (" SIGILL");
		if (sigismember (&sigset, SIGTRAP))
			printf (" SIGTRAP");
		if (sigismember (&sigset, SIGABRT))
			printf (" SIGABRT");
		if (sigismember (&sigset, SIGIOT))
			printf (" SIGIOT");
		if (sigismember (&sigset, SIGBUS))
			printf (" SIGBUS");
		if (sigismember (&sigset, SIGFPE))
			printf (" SIGFPE");
		if (sigismember (&sigset, SIGKILL))
			printf (" SIGKILL");
		if (sigismember (&sigset, SIGUSR1))
			printf (" SIGUSR1");
		if (sigismember (&sigset, SIGSEGV))
			printf (" SIGSEGV");
		if (sigismember (&sigset, SIGUSR2))
			printf (" SIGUSR2");
		if (sigismember (&sigset, SIGPIPE))
			printf (" SIGPIPE");
		if (sigismember (&sigset, SIGALRM))
			printf (" SIGALRM");
		if (sigismember (&sigset, SIGTERM))
			printf (" SIGTERM");
		if (sigismember (&sigset, SIGSTKFLT))
			printf (" SIGSTKFLT");
		if (sigismember (&sigset, SIGCHLD))
			printf (" STGCHLD");
		if (sigismember (&sigset, SIGCONT))
			printf (" SIGCONT");
		if (sigismember (&sigset, SIGSTOP))
			printf (" SIGSTOP");
		if (sigismember (&sigset, SIGTSTP))
			printf (" SIGTSTP");
		if (sigismember (&sigset, SIGTTIN))
			printf (" SIGTTIN");
		if (sigismember (&sigset, SIGTTOU))
			printf (" SIGTTOU");
		if (sigismember (&sigset, SIGURG))
			printf (" SIGURG");
		if (sigismember (&sigset, SIGXCPU))
			printf (" SIGXCPU");
		if (sigismember (&sigset, SIGXFSZ))
			printf (" SIGXFSZ");
		if (sigismember (&sigset, SIGVTALRM))
			printf (" SIGVTALRM");
		if (sigismember (&sigset, SIGPROF))
			printf (" SIGPROF");
		if (sigismember (&sigset, SIGWINCH))
			printf (" SIGWINCH");
		if (sigismember (&sigset, SIGIO))
			printf (" SIGIO");
		if (sigismember (&sigset, SIGPWR))
			printf (" SIGPWR");
		if (sigismember (&sigset, SIGSYS))
			printf (" SIGSYS");
		printf ("\n");
	}

	errno = errno_save;
}

