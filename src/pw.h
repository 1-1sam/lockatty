#include <stdio.h>
#include <ncursesw/ncurses.h>
#include <openssl/md5.h>
#include <string.h>

void create_pw_file(char* str);
int lpwcmp(char* guess);
