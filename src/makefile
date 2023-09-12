include makefile.inc

NOW = $(shell date +"%Y-%m-%d(%H:%M:%S %z)")

# Extra destination directories
PKGDIR = ./output/$(MACHINE)/pkg/

# targets
all:
	$(MAKE) -C src all

clean:
	$(MAKE) -C src clean

install: all
	$(INSTALL) -D -p -m 0644 odl/my-manager-definition.odl $(DEST)/etc/amx/$(COMPONENT)/my-manager-definition.odl
	$(INSTALL) -D -p -m 0755 odl/my-manager.odl $(DEST)/etc/amx/$(COMPONENT)/my-manager.odl
	$(INSTALL) -d -m 0755 $(DEST)$(BINDIR)
	ln -sfr $(DEST)/usr/bin/amxrt $(DEST)$(BINDIR)/$(COMPONENT)
	$(INSTALL) -D -p -m 0644 output/$(MACHINE)/$(COMPONENT).so $(DEST)/usr/lib/amx/$(COMPONENT)/$(COMPONENT).so
	$(INSTALL) -D -p -m 0755 scripts/$(COMPONENT).sh $(DEST)$(INITDIR)/$(COMPONENT)

package: all
	$(INSTALL) -D -p -m 0644 odl/my-manager-definition.odl $(PKGDIR)/etc/amx/$(COMPONENT)/my-manager-definition.odl
	$(INSTALL) -D -p -m 0755 odl/my-manager.odl $(PKGDIR)/etc/amx/$(COMPONENT)/my-manager.odl
	$(INSTALL) -d -m 0755 $(PKGDIR)$(BINDIR)
	ln -sfr $(PKGDIR)/usr/bin/amxrt $(PKGDIR)$(BINDIR)/$(COMPONENT)
	$(INSTALL) -D -p -m 0644 output/$(MACHINE)/$(COMPONENT).so $(PKGDIR)/usr/lib/amx/$(COMPONENT)/$(COMPONENT).so
	$(INSTALL) -D -p -m 0755 scripts/$(COMPONENT).sh $(PKGDIR)$(INITDIR)/$(COMPONENT)
	cd $(PKGDIR) && $(TAR) -czvf ../$(COMPONENT)-$(VERSION).tar.gz .
	cp $(PKGDIR)../$(COMPONENT)-$(VERSION).tar.gz .

.PHONY: all clean install package
