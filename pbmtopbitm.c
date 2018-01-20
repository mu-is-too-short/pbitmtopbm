/*
 * pbmtopbitm.c
 *	PBM to Pilot bitmap. This converter outputs the format the
 *	txt2bitm from prc-tools expects.
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
MU_ID("$Mu: pbitmtopbm/pbmtopbitm.c 1.11 1998/12/18 19:47:18 $")

#include <mine/common.h>

typedef struct {
	bit	**bitmap;	/* the bitmap, unpacked	*/
	int	rows, cols;	/* bitmap size		*/
	char	one, zero;	/* on/off characters	*/
} SLOP;

/*
 * Valid off/zero characters.  Technically I'm not allowed to
 * use "is[a-z]+" as a name here (all such names are reserved for
 * the standard libraries) but I'm going to live dangerously and
 * openly flaunt the standard (obviously my next step will be
 * blowing up french-fry trucks on crowded down-town streets
 * or some other equally unsociable act).
 */
#define	iszerochar(c)	((c) == ' ' || (c) == '-')

/*
 * Default zero and one characters.
 */
#define	CZERO	'-'
#define	CONE	'#'

static int
readit(SLOP *s, FILE *fp)
{
	bit	**bitmap;
	int	rows, cols;

	if((bitmap = pbm_readpbm(fp, &cols, &rows)) == NULL)
		return E_BADPBM;
	s->bitmap = bitmap;
	s->rows   = rows;
	s->cols   = cols;

	return 0;
}

static int
writeit(SLOP *s, FILE *fp)
{
	int	r, c;
	char	*buf;

	if(s->cols > MAXCOLS)
		return E_TOOLONG;

	if((buf = calloc(s->cols + 2, 1)) == NULL)
		return ENOMEM;
	buf[s->cols] = '\n';
	for(r = 0; r < s->rows; ++r) {
		for(c = 0; c < s->cols; ++c)
			buf[c] = s->bitmap[r][c] == 0 ? s->zero : s->one;
		fputs(buf, fp);
	}
	free((void *)buf);

	return 0;
}

static int
version(const char *me)
{
	printf("%s %s\n", me, VERSION);
	return EXIT_SUCCESS;
}

#define	OPTS	"hvo:z:"
char *explain[] = {
	"\tConvert a pbm file to a pbitm file.",
	"",
	"\t-h    Display this usage message and exit.",
	"\t-v    Display the version number and exit.",
	"\t-o c  Specify the character for one (on) bits, 'c' should be",
	"\t      anything but space or '-'",
	"\t-z c  Specify the character for zero (off) bits, 'c' should be",
	"\t      a space or '-'.",
	NULL
};
static int
usage(const char *me, int ret)
{
	char	**s;

	printf("%s [-hv] [-o c] [-z c] [in [out]]\n", me);
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
	s.one  = CONE;
	s.zero = CZERO;
	pbm_init(&argc, argv);
	while((i = getopt(argc, argv, OPTS)) != EOF) {
		switch(i) {
		case 'h':	exit(usage(me, EXIT_SUCCESS));		break;
		case 'v':	exit(version(me));			break;
		case 'o':	s.one  = *optarg;			break;
		case 'z':	s.zero = *optarg;			break;
		default:	exit(usage(me, EXIT_FAILURE));		break;
		}
	}
	if(iszerochar(s.one))
		die("Invalid on/one character: %c\n", s.one);
	if(!iszerochar(s.zero))
		die("Invalid off/zero character: %c\n", s.zero);

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

	pbm_freearray(s.bitmap, s.rows);

	if(in != stdin)
		fclose(in);
	if(out != stdout)
		fclose(out);

	return EXIT_SUCCESS;
}
