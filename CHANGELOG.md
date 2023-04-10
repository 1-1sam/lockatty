# Changelog -- lockatty 1.0.0

## Added
* Added program options: -e or --echo, -l or --lockatty-pw, -n or --no-text-prompt, -? or --help, --usage, and
-V or --version.
* Created a manual.
* Support for users' system passwords.
* Warning for passwords that exceed the 50 character limit.

## Changes
* Seperated lockatty.c into multiple c and header files in src directory.
* The echo file is now a program option which accepts any ascii file passed to it.
* ~/.lockatty/pw is now ~/.pw.
* Updated Makefile.
* Updated README.md.

## Removed
* Removed ~/.lockatty folder.
* Removed ~/.lockatty/echo file. Please use the -e option from now on.

## Fixes
* Fixed cat_echo(). Can now properly read files over 1024 bytes. Hopefully, at least.

