#ifndef TRE_MFASTMATCH_H
#define TRE_MFASTMATCH_H 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <mregex.h>
#include <regex.h>

#include "tre-internal.h"

#define WM_MAXPAT 64

#define MHEUR_NONE 0
#define MHEUR_PREFIX 1
#define MHEUR_LONGEST 2
#define MHEUR_LITERAL 3
#define MHEUR_SINGLE 4

typedef struct {
	int cflags;
	char **pat;		/* Patterns */
	size_t *siz;		/* Pattern sizes */
	size_t n;		/* No of patterns */
        size_t m;		/* Shortest pattern length */
	size_t defsh;		/* Default shift */
	void *shift;		/* Wu-Manber shift table */
#ifdef TRE_WCHAR
	tre_char_t **wpat;	/* Patterns (wide) */
	size_t *wsiz;		/* Pattern sizes (wide) */
	size_t wn;		/* No of patterns (wide) */
	size_t wm;		/* Shortest pattern length (wide) */
	size_t wdefsh;		/* Default shift (wide) */
	void *wshift;		/* Wu-Manber shift table (wide) */
#endif
} wmsearch_t;

typedef struct {
	size_t shift;			/* Shift value for fragment */
	size_t suff;			/* No of pats ending w/ fragment */
	uint8_t suff_list[WM_MAXPAT];	/* Pats ending w/ fragment */
	size_t pref;			/* No of pats starting w/ fragment */
	uint8_t pref_list[WM_MAXPAT];	/* Pats starting w/ fragment */
} wmentry_t;

int
tre_wmcomp(wmsearch_t *wm, size_t nr, const tre_char_t **regex,
	   size_t *n, int cflags);
int
tre_wmexec(const wmsearch_t *wm, const void *str, size_t len,
	   tre_str_type_t type, size_t nmatch, regmatch_t pmatch[],
	   int eflags);
void
tre_wmfree(wmsearch_t *wm);
#endif				/* TRE_MFASTMATCH_H */
