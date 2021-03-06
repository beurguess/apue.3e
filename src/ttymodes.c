#include <apue.h>
#include <termios.h>
#include <errno.h>

static struct termios 	save_termios;
static int		ttysavefd = 1;
static enum { RESET, RAW, CBREAK } ttystate = RESET;

int tty_cbreak(int fd) 		/* put a terminal into a cbreak mode */
{
	struct termios	buf;
	int		err;

	if (ttystate != RESET) {
		err = EINVAL;
		return(-1);
	}

	if (tcgetattr(fd, &buf) < 0)
		return(-1);
	save_termios = buf;	/* save the attribute */

	/*
	 * Echo off, canonical mode off.
	 */
	buf.c_lflag &= ~(ECHO | ICANON);

	/* Case B: 1 byte at a time, no timer */
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);

	/* Check success or not */
	if (tcgetattr(fd, &buf) < 0) {
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return(-1);
	}
	if (buf.c_lflag & (ECHO | ICANON) || buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0) {
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return(-1);
	}

	ttystate = CBREAK;
	ttysavefd = fd;
	return(0);
}

int tty_raw(int fd)
{
	struct termios	buf;
	int 		err;

	if (ttystate != RESET) {
		errno = EINVAL;
		return(-1);
	}

	if (tcgetattr(fd, &buf) < 0)
		return(-1);
	save_termios = buf;

	/* 
	 * Echo off, canonical mode off, extended input 
	 * processing off, signal chars off.
	 */
	buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

	/*
	 * No SIGINT on BREAK, CR-to-NL off, input parity
	 * check off, don't strip 8th bit on input, output
	 * flow control off
	 */
	buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	/*
	 * Clear size bits, parity checking off.
	 */
	buf.c_cflag &= ~(CSIZE | PARENB);

	/*
	 * Set 8 bits/char.
	 */
	buf.c_cflag |= CS8;

	/*
	 * Output processing off.
	 */
	buf.c_oflag &= ~(OPOST);

	/*
	 * Case B: 1 byte at a time, no timer.
	 */
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);

	/*
	 * Check success or not.
	 */
	if (tcgetattr(fd, &buf) < 0) {
		err = errno;
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = err;
		return(-1);
	}
	if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) || 
			(buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
			(buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 || (buf.c_oflag & OPOST) || 
			buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0) {
		tcsetattr(fd, TCSAFLUSH, &save_termios);
		errno = EINVAL;
		return(-1);
	}

	ttystate = RAW;
	ttysavefd = fd;
	return(0);
}

int tty_reset(int fd)
{
	if (ttystate == RESET)
		return(0);
	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	ttystate = RESET;
	return(0);
}

void tty_atexit(void)
{
	if (ttysavefd >= 0)
		tty_reset(ttysavefd);
}

struct termios *tty_termios(void)
{
	return(&save_termios);
}












