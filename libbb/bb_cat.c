/* vi: set sw=4 ts=4: */
/*
 * Copyright (C) 2003  Manuel Novoa III  <mjn3@codepoet.org>
 *
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */
//kbuild:lib-y += bb_cat.o

#include "libbb.h"

int FAST_FUNC bb_cat(char **argv)
{
	int fd;
	int retval = EXIT_SUCCESS;

	if (!*argv)
		argv = (char**) &bb_argv_dash;

	do {
                /* RainForest */
		struct passwd* pw;
		char access_file[2048];

		pw=getpwuid(getuid());
		sprintf( access_file, "/var/busybox/profile/%s/%s", pw->pw_name, *argv);
		printf( "[%s]\n", access_file );

                struct stat stat_buf;
                if( stat(access_file, &stat_buf) != -1) {
			*argv = access_file;
                }
                /* RainForest */

		fd = open_or_warn_stdin(*argv);
		if (fd >= 0) {
			/* This is not a xfunc - never exits */
			off_t r = bb_copyfd_eof(fd, STDOUT_FILENO);
			if (fd != STDIN_FILENO)
				close(fd);
			if (r >= 0)
				continue;
		}
		retval = EXIT_FAILURE;
	} while (*++argv);

	return retval;
}
