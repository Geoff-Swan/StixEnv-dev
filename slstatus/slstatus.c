/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>

#include "arg.h"
#include "slstatus.h"
#include "util.h"

// COMMENTS MAKE HACKING EASY; even though this code is wonderfully written to make 'hacking' straightfoward, I'm 
// still a moron and it still took me the best part of an hour to decipher most of it; I still only understand just
// enough to have applied the changes I have

struct arg {
	const char *(*func)(const char *);
	const char *fmt;
	const char *args;
};

char buf[1024];
static volatile sig_atomic_t done;
static Display *dpy;

#include "config.h"

static void
terminate(const int signo)
{
	if (signo != SIGUSR1)
		done = 1;
}

static void
difftimespec(struct timespec *res, struct timespec *a, struct timespec *b)
{
	res->tv_sec = a->tv_sec - b->tv_sec - (a->tv_nsec < b->tv_nsec);
	res->tv_nsec = a->tv_nsec - b->tv_nsec +
	               (a->tv_nsec < b->tv_nsec) * 1E9;
}

static void
usage(void)
{
	die("usage: %s [-v] [-s] [-1]", argv0);
}

int
main(int argc, char *argv[])
{
	struct sigaction act;
	struct timespec start, current, diff, intspec, wait;
	size_t i, len;
	int sflag, ret;
	char status[MAXLEN];
	const char *res;

	sflag = 0;
	ARGBEGIN {
	case 'v':
		die("slstatus-"VERSION);
	case '1':
		done = 1;
		/* FALLTHROUGH */
	case 's':
		sflag = 1;
		break;
	default:
		usage();
	} ARGEND

	if (argc)
		usage();

	memset(&act, 0, sizeof(act));
	act.sa_handler = terminate;
	sigaction(SIGINT,  &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	act.sa_flags |= SA_RESTART;
	sigaction(SIGUSR1, &act, NULL);

	if (!sflag && !(dpy = XOpenDisplay(NULL)))
		die("XOpenDisplay: Failed to open display");

	do {
		if (clock_gettime(CLOCK_MONOTONIC, &start) < 0) //Die if clock fails to get time
			die("clock_gettime:"); 

		status[0] = 'a'; //'status' is the char array that stores what gets printed to the screen

		for (i = len = 0; i < LEN(args); i++) { //iterate over the 'args' array - struct 'args'

			if (!(res = args[i].func(args[i].args))) //try running args[i].func and store the result in 'res'
				res = unknown_str; //if that fails, append the pre-defined 'unknown_str' (found in config.h)

			//append 'res' to status, increasing the length of status by 'len'
			//		     TARGET 				 Fstring      APPEND 
			if ((ret = esnprintf(status + len, sizeof(status) - len, args[i].fmt, res)) < 0)
				break; //if esnprintf returns an error, break

			len += ret; //esnprintf returns ret, the length of the string added to status
		}

		if (sflag) {
			puts(status);
			fflush(stdout);
			if (ferror(stdout))
				die("puts:");
		} else {
			if (XStoreName(dpy, DefaultRootWindow(dpy), status) < 0)
				die("XStoreName: Allocation failed");
			XFlush(dpy);
		}

		if (!done) {
			if (clock_gettime(CLOCK_MONOTONIC, &current) < 0)
				die("clock_gettime:");
			difftimespec(&diff, &current, &start);

			intspec.tv_sec = interval / 1000;
			intspec.tv_nsec = (interval % 1000) * 1E6;
			difftimespec(&wait, &intspec, &diff);

			if (wait.tv_sec >= 0 &&
			    nanosleep(&wait, NULL) < 0 &&
			    errno != EINTR)
					die("nanosleep:");
		}
	} while (!done);

	if (!sflag) {
		XStoreName(dpy, DefaultRootWindow(dpy), NULL);
		if (XCloseDisplay(dpy) < 0)
			die("XCloseDisplay: Failed to close display");
	}

	return 0;
}
