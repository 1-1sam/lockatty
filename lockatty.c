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

#define STRCMP_EQUAL 0
#define MAX_PW_LEN 50
#define MD5_LEN 32
#define FOREVER_MAN 1

void check_pw_file();
void create_pw_file(char* str);
int check_file(char* filename);
void cat_echo();
int pwcmp(char* guess);

int main(void) {

    char pwguess[MAX_PW_LEN];

    /* Flying to the home directory for the winter. */
    chdir(getenv("HOME"));

    /* Create .lockatty in home if it does not exist. This is where all user files are stored. */
    if (check_file(".lockatty/") == 0) {
        mkdir(".lockatty",0755);
    }

    initscr();
    noecho();

    check_pw_file();

    if (check_file(".lockatty/echo")) {
        cat_echo();
    }

    while (FOREVER_MAN) {
        printw("Please enter your password:\n");
        refresh();
        getstr(pwguess);

        if ((pwcmp(pwguess))) {
            /* Correct password */
            endwin();
            return 0;
        } else {
            printw("Incorrect. Try again. \n");
            refresh();
        }
    }
    return 1;
}

void check_pw_file() {
    char pw1[MAX_PW_LEN];
    char pw2[MAX_PW_LEN];
    while (check_file(".lockatty/pw") == 0) {

        printw("A password has not been set yet. Please enter the password you would like to use:\n");
        getstr(pw1);
        printw("Enter your password again.\n");
        getstr(pw2);
        if ((strcmp(pw1,pw2)) == STRCMP_EQUAL) {
            create_pw_file(pw1);
            printw("Password set.\n");
        } else {
        	printw("Passwords do match.\n");
        }
    }
}

void create_pw_file(char* str) {

    FILE* password_file;
    unsigned char digest[16];

    password_file = fopen(".lockatty/pw","w");

    MD5(str, strlen(str), digest);

    /* Send the digest to .lockatty/pw in a hexadecimal format. */
    for (int i = 0; i < 16; i++) {
        fprintf(password_file, "%02x", (unsigned int) digest[i]);
    }

    fclose(password_file);
}

int check_file(char* filename) {
    FILE *file;
    if((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}

/* Occasional memory leaks here */
void cat_echo() {
    FILE* echo;
    char buf[1024];

    fopen(".lockatty/echo","r");

    buf[1023] = '\0'; /* This terminating null should never be overwritten. */
    do {
    	memset(buf, 0, 1022);
        fread(buf, 1, 1023, echo);
        printw("%s",buf);
    } while (buf[1022]);
	printw("\n");
    fclose(echo);
}

int pwcmp(char* guess) {
    FILE* password_file;
    char buf[MD5_LEN + 1];
    char guess_md5[MD5_LEN + 1];
    unsigned char guess_digest[16];
    char tmp02x[6];

    password_file = fopen(".lockatty/pw","r");

    fread(buf,MD5_LEN,1,password_file);
    buf[MD5_LEN] = '\0';

    MD5(guess, strlen(guess), guess_digest);

    /* Setting the first character in character_md5 to 0 will prevent a memory leak. */
    guess_md5[0] = '\0';

    /* Writes the hexadecimal number of guess_digest[i] to tmp02x, which is then appended to guess_md5 */
    for (int i = 0; i < 16; i++) {
        sprintf(tmp02x,"%02x",(unsigned int) guess_digest[i]);
        strcat(guess_md5,tmp02x);
    }

    /* A d is added to the beginning of the guess_md5. This only happens in tty, not tmux */
    guess_md5[MD5_LEN] = '\0';

    if ((strcmp(buf,guess_md5)) == STRCMP_EQUAL) {
        return 1;
    }
    return 0;
}
