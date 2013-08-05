/* transRegCodeCondition.c was originally generated by the autoSql program, which also 
 * generated transRegCodeCondition.h and transRegCodeCondition.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "transRegCodeCondition.h"


void transRegCodeConditionStaticLoad(char **row, struct transRegCodeCondition *ret)
/* Load a row from transRegCodeCondition table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->growthCondition = row[1];
}

struct transRegCodeCondition *transRegCodeConditionLoad(char **row)
/* Load a transRegCodeCondition from row fetched with select * from transRegCodeCondition
 * from database.  Dispose of this with transRegCodeConditionFree(). */
{
struct transRegCodeCondition *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->growthCondition = cloneString(row[1]);
return ret;
}

struct transRegCodeCondition *transRegCodeConditionLoadAll(char *fileName) 
/* Load all transRegCodeCondition from a whitespace-separated file.
 * Dispose of this with transRegCodeConditionFreeList(). */
{
struct transRegCodeCondition *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = transRegCodeConditionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct transRegCodeCondition *transRegCodeConditionLoadAllByChar(char *fileName, char chopper) 
/* Load all transRegCodeCondition from a chopper separated file.
 * Dispose of this with transRegCodeConditionFreeList(). */
{
struct transRegCodeCondition *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = transRegCodeConditionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct transRegCodeCondition *transRegCodeConditionCommaIn(char **pS, struct transRegCodeCondition *ret)
/* Create a transRegCodeCondition out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new transRegCodeCondition */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->growthCondition = sqlStringComma(&s);
*pS = s;
return ret;
}

void transRegCodeConditionFree(struct transRegCodeCondition **pEl)
/* Free a single dynamically allocated transRegCodeCondition such as created
 * with transRegCodeConditionLoad(). */
{
struct transRegCodeCondition *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->growthCondition);
freez(pEl);
}

void transRegCodeConditionFreeList(struct transRegCodeCondition **pList)
/* Free a list of dynamically allocated transRegCodeCondition's */
{
struct transRegCodeCondition *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    transRegCodeConditionFree(&el);
    }
*pList = NULL;
}

void transRegCodeConditionOutput(struct transRegCodeCondition *el, FILE *f, char sep, char lastSep) 
/* Print out transRegCodeCondition.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->growthCondition);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */
