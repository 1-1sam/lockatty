# lockatty
<a> <img src=lockatty-scrot.png></a>

lockatty is a simple screenlocker for Linux terminals.
## Usage
By default, lockatty will use your user's system password for authentication. If you wish to use a seperate password
just for lockatty, you can use the -l option which will prompt you to set a password and save its hash to ~/.pw. If
you wish to reset this password, you can delete the .pw file and it will prompt you again when the -l option is
invoked again.

The -e option can be used to print the contents of a given ascii file to the prompt like in the example screenshot. The
text prompt asking for your password can be disabled with the -n option. The text informing you of an incorrect password
attempt will still be printed, however.
## Install
Required dependencies are openssl and ncurses.

This will install it into /usr/local.
```bash
make
make install # as root
make clean
```
You may edit the DESTDIR and PREFIX variable to install it in your preferred directory.
```bash
make install DESTDIR=build PREFIX=/usr
```
It is recommended you install the documentation.
```bash
make install-doc DESTDIR=build PREFIX=/usr
```

If you wish to uninstall:
```bash
make uninstall # Make sure you specify DESTDIR and PREFIX if they were used during the make install.
```

## TODO

* [X] Add support for options.
* [X] Add support for user's system passwords.
* [ ] Add support for other hashing algorithims besides md5.

## License
[GPL-3](https://www.gnu.org/licenses/gpl-3.0-standalone.html)
