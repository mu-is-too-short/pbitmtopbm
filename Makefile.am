# @(#)$Mu: pbitmtopbm/Makefile.am 1.2 1998/12/18 20:01:58 $
##
## Makefile.am
##	automake file for pbitmtopbm.
##
## Copyright (C) 1998 Eric A. Howe
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
##   Authors:	Eric A. Howe (mu@trends.net)
##

bin_PROGRAMS = pbitmtopbm pbmtopbitm
pbitmtopbm_SOURCES = pbitmtopbm.c common.c
pbmtopbitm_SOURCES = pbmtopbitm.c common.c

pbitmtopbm_LDADD = @PBM_LIBS@
pbmtopbitm_LDADD = @PBM_LIBS@

man_MANS = pbitmtopbm.1 pbmtopbitm.1

MAINTAINERCLEANFILES = aclocal.m4 Makefile.in configure

DISTCLEANFILES = pbitmtopbm.1 pbmtopbitm.1

INCLUDES = -I.
