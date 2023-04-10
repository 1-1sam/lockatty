/*
Various password handling functions used by lockatty.
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

#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <openssl/md5.h>
#include <string.h>

#include "file.h"

#define STRCMP_EQUAL 0
#define MAX_PW_LEN 50
#define MD5_LEN 32

void create_pw_file(char* str) {

    FILE* password_file;
    unsigned char digest[16];

    password_file = fopen(".pw","w");

    MD5(str, strlen(str), digest);

    /* Send the digest to .lockatty/pw in a hexadecimal format. */
    for (int i = 0; i < 16; i++) {
        fprintf(password_file, "%02x", (unsigned int) digest[i]);
    }

    fclose(password_file);
}

int lpwcmp(char* guess) {
    FILE* password_file;
    char buf[MD5_LEN + 1];
    char guess_md5[MD5_LEN + 1];
    unsigned char guess_digest[16];
    char tmp02x[6];

    password_file = fopen(".pw","r");

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

    guess_md5[MD5_LEN] = '\0';

    if ((strcmp(buf,guess_md5)) == STRCMP_EQUAL) {
        return 1;
    }
    return 0;
}
