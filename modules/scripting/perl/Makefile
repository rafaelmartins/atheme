# Copyright (c) 2010 Atheme Development Group
# Rights to this code are documented in doc/LICENSE.

PLUGIN = perl$(PLUGIN_SUFFIX)

SRCS = perl_module.c perlxsi.c

SUBDIRS = api

include ../../../extra.mk
include ../../../buildsys.mk

plugindir = $(MODDIR)/modules/scripting

CPPFLAGS += -I../../../include -I. $(shell perl -MExtUtils::Embed -e ccopts)
CFLAGS += $(PLUGIN_CFLAGS)
LDFLAGS += $(PLUGIN_LDFLAGS) $(shell perl -MExtUtils::Embed -e ldopts)
LIBS +=	-L../../../libathemecore -lathemecore ${LDFLAGS_RPATH}

perlxsi.c:
	perl -MExtUtils::Embed -e xsinit

install-extra:
	${MKDIR_P} ${plugindir}/lib
	${INSTALL} -m644 -t ${plugindir}/lib lib/*.pl lib/*.pm
	${MKDIR_P} ${plugindir}/lib/Atheme
	${INSTALL} -m644 -t ${plugindir}/lib/Atheme lib/Atheme/*.pm