/*
lockatty, a simple terminal screenlocker.
Copyright 2023, Samuel Young

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Contact: samyoung12788@gmail.com
*/

#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <argp.h>

#include "pw.h"
#include "file.h"
#include "shadow-auth.h"

#define STRCMP_EQUAL 0
#define MAX_PW_LEN 50
#define MD5_LEN 32
#define FOREVER_MAN 1

/* Getting argp ready */
const char* argp_program_version = "lockatty 1.0.0";
const char* argp_program_bug_address = "samyoung12788@gmail.com";
static char doc[] = "lockatty -- Simple terminal screen locker";
static char args_doc[] = "";

static struct argp_option options[] = {
	{ "lockatty-pw", 'l', 0, 0, "Use a lockatty-specific password rather than a user's system password." },
	{ "echo", 'e', "FILE", 0, "Echo the contents of an ascii file for the password prompt. Must pass absolute path for file." },
	{ "no-text-prompt", 'n', 0, 0, "Does not display the text prompt asking for the password."},
	{ 0 }
};

struct arguments {
	enum { SYSTEM_PW, LOCKATTY_PW } pw_type;
	int echoing;
	char* echo_file;
	int text_prompt;
};

static error_t parse_opt (int key, char* arg, struct argp_state* state) {
	struct arguments* arguments = state->input;

	switch (key) {
	case 'l':
		arguments->pw_type = LOCKATTY_PW; break;
	case 'e':
		arguments->echoing = 1;
		arguments->echo_file = arg; break;
	case 'n':
		arguments->text_prompt = 0; break;
	case ARGP_KEY_ARG:
		return 0; break;
	default:
		return ARGP_ERR_UNKNOWN; break;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };
/* Done setting argp up. */

int main(int argc, char** argv) {

    char pwguess[MAX_PW_LEN];
	char pw1[MAX_PW_LEN];
	char pw2[MAX_PW_LEN];
	int auth;

	struct arguments arguments;
	arguments.pw_type = SYSTEM_PW;
    arguments.echoing = 0;
    arguments.text_prompt = 1;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    /* Flying to the home directory for the winter. */
    chdir(getenv("HOME"));

    initscr();
    noecho();

	/* Create the pw file if it does not exist already. Only if using a lockatty password. */
	if (arguments.pw_type == LOCKATTY_PW) {
		printw("A lockatty password has not been set yet. Please enter the password you would like to you.\n");
		while (check_file(".pw") == 0) {
			getstr(pw1);
			printw("Please enter your password again.\n");
			getstr(pw2);
			if ((strcmp(pw1,pw2)) == 0 && strlen(pw1) <= 51) {
				create_pw_file(pw1);
				printw("Password set.\n");
			} else {
				printw("Passwords do not match or are over 50 characters long.\n");
			}
		}
	}

	if (arguments.echoing && check_file(arguments.echo_file)) {
		cat_echo(arguments.echo_file);
	}

	if (arguments.text_prompt) {
		printw("Please enter your password.\n");
		refresh();
	}

	for (;;) {
		getstr(pwguess);

		if (arguments.pw_type == SYSTEM_PW) {
			auth = shadow_auth(pwguess);
		} else if (arguments.pw_type == LOCKATTY_PW) {
			auth = lpwcmp(pwguess);
		}

		if (auth) {
			endwin();
			return 0;
		} else {
			printw("Incorrect.\n");
		}
	}
	return 0;
}
