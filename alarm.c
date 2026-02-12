#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FMT_DATE  "%Y-%m-%d (%a)"
#define FMT_TIME  "%H:%M:%S"

typedef unsigned int uint;

void
main(int argc, char *argv[])
{
	if (0) {
	error:
		printf("%s Interval Remainder\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (argc != 3)
		goto error;

	const uint interval = atoi(argv[1]);
	const uint remainder = atoi(argv[2]);
	if (!interval || interval <= remainder)
		goto error;

	char *env_dsp = getenv("DISPLAY");
	if (env_dsp == NULL) {
		fprintf(stderr, "Envvar DISPLAY not defined\n");
		exit(EXIT_FAILURE);
	}

	Display* dsp = XOpenDisplay(env_dsp);
	if (dsp == NULL) {
		fprintf(stderr, "XOpenDisplay error\n");
		exit(EXIT_FAILURE);
	}

	Window win = DefaultRootWindow(dsp);

	struct timespec ts = {.tv_sec = 1, .tv_nsec = 0};
	struct tm *tm;
	char date_buf[20], time_buf[20];

	do {
		printf("\033[2J\033[;1H");

		time_t now = time(NULL);

		tm = localtime(&now);
		strftime(time_buf, sizeof(date_buf), FMT_TIME, tm);
		strftime(date_buf, sizeof(time_buf), FMT_DATE, tm);
		printf("%s %s\n", date_buf, time_buf);

		int cur = now % interval;
		printf("Int: %d / Rem: %d / Cur: %d\n", interval, remainder, cur);

		if (cur == remainder) {
			XStoreName(dsp, win, time_buf);
			XFlush(dsp);
		}

		fflush(stdout);
	} while (nanosleep(&ts, NULL) == 0);

	XCloseDisplay(dsp);
	exit(EXIT_SUCCESS);
}
