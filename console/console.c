#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "auto/config.h"

struct termios orig_termios;

typedef struct {

	int  rows;
	int  cols;

	uint16_t  x;
	uint16_t  y;

	char     buf[CONFIG_CONSOLE_BUFFER_LEN];
	uint8_t  k;

} console_t;

console_t console;


#define PROMPT_ASCII_LEN 9

char prompt[] = "\x1b[94m#0000 \x1b[92m~ \x1b[37m";

int CON_disable()
{
	write(STDOUT_FILENO, "\n\r", 2);
	return tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int CON_enable()
{
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) return -1;

	struct termios raw = orig_termios;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	return tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void CON_prompt()
{
	console.x = PROMPT_ASCII_LEN;
	write(STDOUT_FILENO, prompt, sizeof(prompt));
}

void CON_update_cursor()
{
	char buf[32];

	int n = snprintf(buf, 32, "\x1b[%d;%dH", console.y, console.x);

	if (n > 0) write(STDOUT_FILENO, buf, n);
}

void CON_clean()
{
	console.buf[console.k] = '\0';
	console.x = 0;
	console.y = 1;
	console.k = 0;

	write(STDOUT_FILENO, "\x1b[2J", 4);
	CON_update_cursor();
	CON_prompt();
}

int CON_update()
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		return -1;
	}

	if (console.rows != ws.ws_row || console.cols != ws.ws_col)
	{
		CON_clean();
	}

	console.rows = ws.ws_row;
	console.cols = ws.ws_col;

	return 0;
}

void CON_breakline()
{
	if (console.y < console.rows)
	{
		console.buf[console.k] = '\0';
		console.x =  0;
		console.k =  0;

		console.y++;

		CON_update_cursor();
		CON_prompt();
	}
	else
	{
		CON_clean();
	}
}

char * CON_capture()
{
	char c = '\0';

	if (read(STDIN_FILENO, &c, 1) != -1)
	{

		// ENTER
		if (c == 13)
		{
			CON_breakline();
			return console.buf;
		}

		// BACKSPACE
		else if (c == 127 && console.k)
		{
			console.x--;

			console.buf[console.k] = '\0'; console.k--;

			CON_update_cursor();
			write(STDIN_FILENO, " ", 1);
			CON_update_cursor();

		}

		// ECHO and CAPTURE
		else if (!iscntrl(c) && console.k < CONFIG_CONSOLE_BUFFER_LEN &&
								console.k < console.cols - PROMPT_ASCII_LEN)
		{
			console.x++;

			console.buf[console.k] = c; console.k++;
			printf("%c", c);
		}
	}

	fflush(stdout);

	return NULL;
}
