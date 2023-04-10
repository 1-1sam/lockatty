PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/share/man

build: src/Makefile
	make -C src

install:
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 4755 -o root -g root src/lockatty $(DESTDIR)$(BINDIR)/lockatty

install-doc:
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	install -o root -m 755 man/lockatty.1 $(DESTDIR)$(MANDIR)/man1
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/lockatty-1.0.0
	install -o root -m 755 LICENSE $(DESTDIR)$(PREFIX)/share/doc/lockatty-1.0.0

clean:
	rm src/lockatty src/*.o

uninstall:
	rm -rf $(DESTDIR)$(BINDIR)/lockatty
	rm -f $(DESTDIR)$(MANDIR)/man1/lockatty.1
	rm -rf $(DESTDIR)$(PREFIX)/share/doc/lockatty-1.0.0
