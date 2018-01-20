/*
 * pbitmtopbm.c
 *	Pilot bitmap to PBM converter.  This converter expects input
 *	in the same format as txt2bitm from prc-tools.
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
MU_ID("$Mu: pbitmtopbm/pbitmtopbm.c 1.17 1998/12/18 20:13:50 $")

#include <mine/common.h>

typedef struct {
	bit	**bitmap;	/* the bits 		*/
	int	rows, cols;	/* size of the bitmap	*/
	int	plain;		/* plain pbm format?	*/
} SLOP;

static int
translate(bit *dst, char *src, int len)
{
	int i;

	for(i = 0; i < len; ++i, ++src, ++dst)
		*dst = (*src != '-' && *src != ' ');

	return 0;
}

static int
readit(SLOP *s, FILE *fp)
{
	char	buf[1024];
	bit	**bitmap;
	int	rows, cols, len, i;

	bitmap = NULL;
	rows   = 0;
	cols   = 0;
	while(fgets(&buf[0], sizeof(buf), fp) != NULL) {
		++rows;
		len = strlen(buf);
		if(buf[len - 1] == '\n')
			buf[--len] = '\0';
		if(cols == 0)
			cols = len;
		else if(len != cols)
			return E_BADROWLEN;
		if(len > MAXCOLS)
			return E_TOOLONG;

		/*
		 * Yes, the dumb slow stupid way.  I could get fancy and
		 * reduce the reallocing but that would just be a waste
		 * of time and effort (and yes, I know this will leak
		 * if the realloc fails).
		 */
		if((bitmap = realloc(bitmap, rows * sizeof(bit *))) == NULL
		|| (bitmap[rows - 1] = calloc(cols, sizeof(bit))) == NULL)
			return ENOMEM;
		if((i = translate(bitmap[rows - 1], buf, len)) != 0)
			return i;
	}

	s->rows   = rows;
	s->cols   = cols;
	s->bitmap = bitmap;

	return 0;
}

static int
writeit(SLOP *s, FILE *fp)
{
	int r;

	pbm_writepbminit(fp, s->cols, s->rows, s->plain);
	for(r = 0; r < s->rows; ++r)
		pbm_writepbmrow(fp, s->bitmap[r], s->cols, s->plain);
	return 0;
}

static int
version(const char *me)
{
	printf("%s %s\n", me, VERSION);
	return EXIT_SUCCESS;
}

#define	OPTS	"hvtb"
static char *explain[] = {
	"\tConvert a pbitm file to a pbm file.",
	"",
	"\t-h\tDisplay this usage message and exit.",
	"\t-v\tDisplay the version number and exit.",
	"\t-t\tForce the pbm file to be in text format.",
	"\t-b\tForce the pbm file to be in raw/binary format.",
	NULL
};
static int
usage(const char *me, int ret)
{
	char	**s;

	printf("%s [-hv] [-t|-b] [in [out]]\n", me);
	for(s = &explain[0]; *s != NULL; ++s)
		printf("%s\n", *s);
	return ret;
}

int
main(int argc, char **argv)
{
	char	*me;
	SLOP	s;
	int	i;
	FILE	*in, *out;

	memset((void *)&s, '\0', sizeof(s));
	if((me = strrchr(*argv, '/')) == NULL)
		me = *argv;
	else
		++me;
	pbm_init(&argc, argv);
	while((i = getopt(argc, argv, OPTS)) != EOF) {
		switch(i) {
		case 'h':	exit(usage(me, EXIT_SUCCESS));		break;
		case 'v':	exit(version(me));			break;
		case 't':	s.plain = 1;				break;
		case 'b':	s.plain = 0;				break;
		default:	exit(usage(me, EXIT_FAILURE));		break;
		}
	}
	in = argv[optind] == NULL ? stdin : fopen(argv[optind++], "r");
	if(in == NULL)
		die("Could not open input %s: %s\n", argv[optind-1],err(errno));
	out = argv[optind] == NULL ? stdout : fopen(argv[optind], "w");
	if(out == NULL)
		die("Could not open output %s: %s\n", argv[optind], err(errno));

	if((i = readit(&s, in)) != 0)
		die("Could not parse input: %s\n", err(i));
	if((i = writeit(&s, out)) != 0)
		die("Could not write output: %s\n", err(i));

	/*
	 * These checks are probably silly but I didn't open stdin or
	 * stdout so I'm not going to close them dammit!
	 */
	if(in != stdin)
		fclose(in);
	if(out != stdout)
		fclose(out);

	return EXIT_SUCCESS;
}
