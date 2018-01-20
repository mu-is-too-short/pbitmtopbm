/*
 * common.c
 *	Common stuff for pbitmtopbm and pbmtopbitm.
 *
 * Copyright (C) 1997 Eric A. Howe
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Authors:  Eric A. Howe (mu@trends.net)
 */
#include <mine/rcs.h>
MU_ID("$Mu: pbitmtopbm/common.c 1.6 1998/12/18 19:47:18 $")

#include <mine/common.h>

char *
err(int e)
{
	char	*s;

	assert(e != 0);
	switch(e) {
	case E_BADROWLEN:	s = "Row with wrong length";		break;
	case E_BADPBM:		s = "Busted pbm file";			break;
	case E_TOOLONG:		s = "Too many columns for pbitm file";	break;
	default:		s = strerror(e);			break;
	}
	return s;
}

void
die(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}
