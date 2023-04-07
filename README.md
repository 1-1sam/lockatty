# lockatty
lockatty is a simple screenlocker for Linux terminals.
## Usage
Your first run will prompt you to set a password. lockatty will use its own password as opposed to your user's system password. If you wish to reset your password, you may delete the pw file that was placed in your home's .lockatty folder.
lockatty will also look for a file named "echo" in your .lockatty folder. Your echo file should be a simple ascii text file. The contents of this echo file will outputted to the prompt of lockatty. This feature is optional.
## Install
This will install it into /usr/local.
```bash
make
make install doc # doc is not necessary but recommended.
make clean
```
You may edit the DESTDIR and PREFIX variable to install it in your preferred directory.
```bash
make install doc DESTDIR=build PREFIX=/usr
```
If you wish to uninstall:
```bash
make uninstall
```
## License
[GPL-3](https://www.gnu.org/licenses/gpl-3.0-standalone.html