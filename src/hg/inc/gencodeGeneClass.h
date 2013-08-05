/* gencodeGeneClass.h was originally generated by the autoSql program, which also 
 * generated gencodeGeneClass.c and gencodeGeneClass.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef GENCODEGENECLASS_H
#define GENCODEGENECLASS_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define GENCODEGENECLASS_NUM_COLS 7

struct gencodeGeneClass
/* Class for Gencode genes */
    {
    struct gencodeGeneClass *next;  /* Next in singly linked list. */
    char *geneId;	/* Gene ID for Gencode gene */
    char *name;	/* Transcript ID for Gencode gene */
    char *transcriptType;	/* Transcript type for Gencode gene */
    int level;	/* Gencode level */
    char *class;	/* Class of gene.  enum('Antisense', 'Antisense_val', 'Artifact', 'Known', 'Novel_CDS', 'Novel_transcript', 'Novel_transcript_val', 'Putative', 'Putative_val', 'TEC', 'Processed_pseudogene', 'Unprocessed_pseudogene', 'Pseudogene_fragment', 'Undefined') */
    char *ottGeneId;	/* Otter Gene id for Gencode gene */
    char *ottTranscriptId;	/* Otter Transcript id for Gencode gene */
    };

void gencodeGeneClassStaticLoad(char **row, struct gencodeGeneClass *ret);
/* Load a row from gencodeGeneClass table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct gencodeGeneClass *gencodeGeneClassLoad(char **row);
/* Load a gencodeGeneClass from row fetched with select * from gencodeGeneClass
 * from database.  Dispose of this with gencodeGeneClassFree(). */

struct gencodeGeneClass *gencodeGeneClassLoadAll(char *fileName);
/* Load all gencodeGeneClass from whitespace-separated file.
 * Dispose of this with gencodeGeneClassFreeList(). */

struct gencodeGeneClass *gencodeGeneClassLoadAllByChar(char *fileName, char chopper);
/* Load all gencodeGeneClass from chopper separated file.
 * Dispose of this with gencodeGeneClassFreeList(). */

#define gencodeGeneClassLoadAllByTab(a) gencodeGeneClassLoadAllByChar(a, '\t');
/* Load all gencodeGeneClass from tab separated file.
 * Dispose of this with gencodeGeneClassFreeList(). */

struct gencodeGeneClass *gencodeGeneClassCommaIn(char **pS, struct gencodeGeneClass *ret);
/* Create a gencodeGeneClass out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gencodeGeneClass */

void gencodeGeneClassFree(struct gencodeGeneClass **pEl);
/* Free a single dynamically allocated gencodeGeneClass such as created
 * with gencodeGeneClassLoad(). */

void gencodeGeneClassFreeList(struct gencodeGeneClass **pList);
/* Free a list of dynamically allocated gencodeGeneClass's */

void gencodeGeneClassOutput(struct gencodeGeneClass *el, FILE *f, char sep, char lastSep);
/* Print out gencodeGeneClass.  Separate fields with sep. Follow last field with lastSep. */

#define gencodeGeneClassTabOut(el,f) gencodeGeneClassOutput(el,f,'\t','\n');
/* Print out gencodeGeneClass as a line in a tab-separated file. */

#define gencodeGeneClassCommaOut(el,f) gencodeGeneClassOutput(el,f,',',',');
/* Print out gencodeGeneClass as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* GENCODEGENECLASS_H */
