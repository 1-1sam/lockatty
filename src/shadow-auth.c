/*
Shadow authentication function used by lockatty.
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

#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>
#include <shadow.h>

int shadow_auth(char* pwg) {
	char* crypt_pwg;
	struct spwd* spw;
	char* user = getenv("USER");

	spw = getspnam(user);

	crypt_pwg = crypt(pwg, spw->sp_pwdp);

	if (strcmp(crypt_pwg,spw->sp_pwdp) == 0) {
		return 1;
	} else {
		return 0;
	}
}
