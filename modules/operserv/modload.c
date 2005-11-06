/*
 * Copyright (c) 2005 William Pitcock, et al.
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Loads a new module in.
 *
 * $Id: modload.c 3601 2005-11-06 23:36:34Z jilles $
 */

#include "atheme.h"

DECLARE_MODULE_V1
(
	"operserv/modload", FALSE, _modinit, _moddeinit,
	"$Id: modload.c 3601 2005-11-06 23:36:34Z jilles $",
	"Atheme Development Group <http://www.atheme.org>"
);

static void os_cmd_modload(char *origin);

command_t os_modload = { "MODLOAD", "Loads a module.",
			 AC_SRA, os_cmd_modload };

list_t *os_cmdtree;

void _modinit(module_t *m)
{
	os_cmdtree = module_locate_symbol("operserv/main", "os_cmdtree");	
	command_add(&os_modload, os_cmdtree);
}

void _moddeinit()
{
	command_delete(&os_modload, os_cmdtree);
}

static void os_cmd_modload(char *origin)
{
	char *module;
	char pbuf[BUFSIZE + 1];

	while((module = strtok(NULL, " ")))
	{

	        if (module_find_published(module))
       		{
                notice(opersvs.nick, origin, "\2%s\2 is already loaded.", module);
                return;
       		}

		logcommand(opersvs.me, user_find(origin), CMDLOG_ADMIN, "MODLOAD %s", module);
		if (*module != '/')
		{
			snprintf(pbuf, BUFSIZE, "%s/%s", PREFIX "/modules",
				 module);
			module_load(pbuf);
		}
		else
			module_load(module);

		notice(opersvs.nick, origin, "Module \2%s\2 loaded.", module);
	}
}
