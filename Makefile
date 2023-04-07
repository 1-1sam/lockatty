PROG=lockatty
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin

$(PROG): lockatty.c
	cc lockatty.c -lcrypto -lncurses -o lockatty

install:
	chmod 755 $(PROG)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(PROG) $(DESTDIR)$(BINDIR)/$(PROG)

clean:
	rm lockatty

uninstall:
	rm -rf $(DESTDIR)$(BINDIR)/$(PROG)
