/* nasmlib.h	header file for nasmlib.c
 *
 * The Netwide Assembler is copyright (C) 1996 Simon Tatham and
 * Julian Hall. All rights reserved. The software is
 * redistributable under the licence given in the file "Licence"
 * distributed in the NASM archive.
 */

#ifndef YASM_NASMLIB_H
#define YASM_NASMLIB_H

/*
 * Wrappers around malloc, realloc and free. nasm_malloc will
 * fatal-error and die rather than return NULL; nasm_realloc will
 * do likewise, and will also guarantee to work right on being
 * passed a NULL pointer; nasm_free will do nothing if it is passed
 * a NULL pointer.
 */
#define nasm_malloc xmalloc
#define nasm_realloc xrealloc
#define nasm_free(p) if (p) xfree(p)
#define nasm_strdup xstrdup
#define nasm_strndup xstrndup
#define nasm_stricmp strcasecmp
#define nasm_strnicmp strncasecmp

/*
 * Convert a string into a number, using NASM number rules. Sets
 * `*error' to TRUE if an error occurs, and FALSE otherwise.
 */
long nasm_readnum(char *str, int *error);

/*
 * Convert a character constant into a number. Sets
 * `*warn' to TRUE if an overflow occurs, and FALSE otherwise.
 * str points to and length covers the middle of the string,
 * without the quotes.
 */
long nasm_readstrnum(char *str, int length, int *warn);

/*
 * seg_init: Initialise the segment-number allocator.
 * seg_alloc: allocate a hitherto unused segment number.
 */
void nasm_seg_init(void);
long nasm_seg_alloc(void);

#ifdef YASM_NASM_H
/*
 * Library routines to manipulate expression data types.
 */
int nasm_is_reloc(nasm_expr *);
int nasm_is_simple(nasm_expr *);
int nasm_is_really_simple (nasm_expr *);
int nasm_is_unknown(nasm_expr *);
int nasm_is_just_unknown(nasm_expr *);
long nasm_reloc_value(nasm_expr *);
long nasm_reloc_seg(nasm_expr *);
long nasm_reloc_wrt(nasm_expr *);
#endif

/*
 * Binary search routine. Returns index into `array' of an entry
 * matching `string', or <0 if no match. `array' is taken to
 * contain `size' elements.
 */
int nasm_bsi (char *string, const char **array, int size);


char *nasm_src_set_fname(char *newname);
long nasm_src_set_linnum(long newline);
long nasm_src_get_linnum(void);
/*
 * src_get may be used if you simply want to know the source file and line.
 * It is also used if you maintain private status about the source location
 * It return 0 if the information was the same as the last time you
 * checked, -1 if the name changed and (new-old) if just the line changed.
 */
int nasm_src_get(long *xline, char **xname);

void nasm_quote(char **str);
char *nasm_strcat(char *one, char *two);

#endif