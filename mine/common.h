/*
 * common.h
 *	Common stuff for pbitmtopbm and pbmtopbitm.
 *
 * Copyright (C) 1997 Eric A. Howe
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Authors:	Eric A. Howe (mu@trends.net)
 */
#ifndef	PBITMTOPBM_COMMON_H
#define	PBITMTOPBM_COMMON_H
MU_HID(pbitmtopbm_common_h, "$Mu: pbitmtopbm/mine/common.h 1.2 1998/12/18 19:49:55 $")

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <pbm.h>

/*
 * Max number of columns for a pbitm file.
 */
#define	MAXCOLS	163

/*
 * These tend to live in different places on different systems so I'm cheating.
 */
extern	int	optind;
extern	char	*optarg;
extern	int	getopt(int, char *const *, const char *);

/*
 * Extra error numbers.
 */
#define	E_BADROWLEN	-1
#define	E_BADPBM	-2
#define	E_TOOLONG	-3

CDECLS_BEGIN
extern	char	*err(int);
extern	void	die(const char *fmt, ...);
CDECLS_END

#endif
