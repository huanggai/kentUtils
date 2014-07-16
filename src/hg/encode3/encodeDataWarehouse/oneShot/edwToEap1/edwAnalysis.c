/* edwAnalysis.c was originally generated by the autoSql program, which also 
 * generated edwAnalysis.h and edwAnalysis.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "edwAnalysis.h"



char *edwAnalysisJobCommaSepFieldNames = "id,commandLine,startTime,endTime,stderr,returnCode,pid,cpusRequested,parasolId";

void edwAnalysisJobStaticLoad(char **row, struct edwAnalysisJob *ret)
/* Load a row from edwAnalysisJob table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->commandLine = row[1];
ret->startTime = sqlLongLong(row[2]);
ret->endTime = sqlLongLong(row[3]);
ret->stderr = row[4];
ret->returnCode = sqlSigned(row[5]);
ret->pid = sqlSigned(row[6]);
ret->cpusRequested = sqlSigned(row[7]);
ret->parasolId = row[8];
}

struct edwAnalysisJob *edwAnalysisJobLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all edwAnalysisJob from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with edwAnalysisJobFreeList(). */
{
struct edwAnalysisJob *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = edwAnalysisJobLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void edwAnalysisJobSaveToDb(struct sqlConnection *conn, struct edwAnalysisJob *el, char *tableName, int updateSize)
/* Save edwAnalysisJob as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. This function automatically escapes quoted strings for mysql. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s',%lld,%lld,'%s',%d,%d,%d,'%s')", 
	tableName,  el->id,  el->commandLine,  el->startTime,  el->endTime,  el->stderr,  el->returnCode,  el->pid,  el->cpusRequested,  el->parasolId);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

struct edwAnalysisJob *edwAnalysisJobLoad(char **row)
/* Load a edwAnalysisJob from row fetched with select * from edwAnalysisJob
 * from database.  Dispose of this with edwAnalysisJobFree(). */
{
struct edwAnalysisJob *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->commandLine = cloneString(row[1]);
ret->startTime = sqlLongLong(row[2]);
ret->endTime = sqlLongLong(row[3]);
ret->stderr = cloneString(row[4]);
ret->returnCode = sqlSigned(row[5]);
ret->pid = sqlSigned(row[6]);
ret->cpusRequested = sqlSigned(row[7]);
ret->parasolId = cloneString(row[8]);
return ret;
}

struct edwAnalysisJob *edwAnalysisJobLoadAll(char *fileName) 
/* Load all edwAnalysisJob from a whitespace-separated file.
 * Dispose of this with edwAnalysisJobFreeList(). */
{
struct edwAnalysisJob *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = edwAnalysisJobLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisJob *edwAnalysisJobLoadAllByChar(char *fileName, char chopper) 
/* Load all edwAnalysisJob from a chopper separated file.
 * Dispose of this with edwAnalysisJobFreeList(). */
{
struct edwAnalysisJob *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = edwAnalysisJobLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisJob *edwAnalysisJobCommaIn(char **pS, struct edwAnalysisJob *ret)
/* Create a edwAnalysisJob out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new edwAnalysisJob */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->commandLine = sqlStringComma(&s);
ret->startTime = sqlLongLongComma(&s);
ret->endTime = sqlLongLongComma(&s);
ret->stderr = sqlStringComma(&s);
ret->returnCode = sqlSignedComma(&s);
ret->pid = sqlSignedComma(&s);
ret->cpusRequested = sqlSignedComma(&s);
ret->parasolId = sqlStringComma(&s);
*pS = s;
return ret;
}

void edwAnalysisJobFree(struct edwAnalysisJob **pEl)
/* Free a single dynamically allocated edwAnalysisJob such as created
 * with edwAnalysisJobLoad(). */
{
struct edwAnalysisJob *el;

if ((el = *pEl) == NULL) return;
freeMem(el->commandLine);
freeMem(el->stderr);
freeMem(el->parasolId);
freez(pEl);
}

void edwAnalysisJobFreeList(struct edwAnalysisJob **pList)
/* Free a list of dynamically allocated edwAnalysisJob's */
{
struct edwAnalysisJob *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    edwAnalysisJobFree(&el);
    }
*pList = NULL;
}

void edwAnalysisJobOutput(struct edwAnalysisJob *el, FILE *f, char sep, char lastSep) 
/* Print out edwAnalysisJob.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->commandLine);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%lld", el->startTime);
fputc(sep,f);
fprintf(f, "%lld", el->endTime);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stderr);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->returnCode);
fputc(sep,f);
fprintf(f, "%d", el->pid);
fputc(sep,f);
fprintf(f, "%d", el->cpusRequested);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->parasolId);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}


char *edwAnalysisSoftwareCommaSepFieldNames = "id,name,version,md5";

void edwAnalysisSoftwareStaticLoad(char **row, struct edwAnalysisSoftware *ret)
/* Load a row from edwAnalysisSoftware table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->name = row[1];
ret->version = row[2];
safecpy(ret->md5, sizeof(ret->md5), row[3]);
}

struct edwAnalysisSoftware *edwAnalysisSoftwareLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all edwAnalysisSoftware from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with edwAnalysisSoftwareFreeList(). */
{
struct edwAnalysisSoftware *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = edwAnalysisSoftwareLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void edwAnalysisSoftwareSaveToDb(struct sqlConnection *conn, struct edwAnalysisSoftware *el, char *tableName, int updateSize)
/* Save edwAnalysisSoftware as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. This function automatically escapes quoted strings for mysql. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s','%s','%s')", 
	tableName,  el->id,  el->name,  el->version,  el->md5);
sqlUpdate(conn, update->string);
freeDyString(&update);
}

struct edwAnalysisSoftware *edwAnalysisSoftwareLoad(char **row)
/* Load a edwAnalysisSoftware from row fetched with select * from edwAnalysisSoftware
 * from database.  Dispose of this with edwAnalysisSoftwareFree(). */
{
struct edwAnalysisSoftware *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
ret->version = cloneString(row[2]);
safecpy(ret->md5, sizeof(ret->md5), row[3]);
return ret;
}

struct edwAnalysisSoftware *edwAnalysisSoftwareLoadAll(char *fileName) 
/* Load all edwAnalysisSoftware from a whitespace-separated file.
 * Dispose of this with edwAnalysisSoftwareFreeList(). */
{
struct edwAnalysisSoftware *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = edwAnalysisSoftwareLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisSoftware *edwAnalysisSoftwareLoadAllByChar(char *fileName, char chopper) 
/* Load all edwAnalysisSoftware from a chopper separated file.
 * Dispose of this with edwAnalysisSoftwareFreeList(). */
{
struct edwAnalysisSoftware *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = edwAnalysisSoftwareLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisSoftware *edwAnalysisSoftwareCommaIn(char **pS, struct edwAnalysisSoftware *ret)
/* Create a edwAnalysisSoftware out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new edwAnalysisSoftware */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->version = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->md5, sizeof(ret->md5));
*pS = s;
return ret;
}

void edwAnalysisSoftwareFree(struct edwAnalysisSoftware **pEl)
/* Free a single dynamically allocated edwAnalysisSoftware such as created
 * with edwAnalysisSoftwareLoad(). */
{
struct edwAnalysisSoftware *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->version);
freez(pEl);
}

void edwAnalysisSoftwareFreeList(struct edwAnalysisSoftware **pList)
/* Free a list of dynamically allocated edwAnalysisSoftware's */
{
struct edwAnalysisSoftware *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    edwAnalysisSoftwareFree(&el);
    }
*pList = NULL;
}

void edwAnalysisSoftwareOutput(struct edwAnalysisSoftware *el, FILE *f, char sep, char lastSep) 
/* Print out edwAnalysisSoftware.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->version);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->md5);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}


char *edwAnalysisStepCommaSepFieldNames = "id,name,softwareCount,software,cpusRequested";

struct edwAnalysisStep *edwAnalysisStepLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all edwAnalysisStep from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with edwAnalysisStepFreeList(). */
{
struct edwAnalysisStep *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = edwAnalysisStepLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void edwAnalysisStepSaveToDb(struct sqlConnection *conn, struct edwAnalysisStep *el, char *tableName, int updateSize)
/* Save edwAnalysisStep as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. This function automatically escapes quoted strings for mysql. */
{
struct dyString *update = newDyString(updateSize);
char  *softwareArray;
softwareArray = sqlStringArrayToString(el->software, el->softwareCount);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s',%d,'%s',%d)", 
	tableName,  el->id,  el->name,  el->softwareCount,  softwareArray ,  el->cpusRequested);
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&softwareArray);
}

struct edwAnalysisStep *edwAnalysisStepLoad(char **row)
/* Load a edwAnalysisStep from row fetched with select * from edwAnalysisStep
 * from database.  Dispose of this with edwAnalysisStepFree(). */
{
struct edwAnalysisStep *ret;

AllocVar(ret);
ret->softwareCount = sqlSigned(row[2]);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
{
int sizeOne;
sqlStringDynamicArray(row[3], &ret->software, &sizeOne);
assert(sizeOne == ret->softwareCount);
}
ret->cpusRequested = sqlSigned(row[4]);
return ret;
}

struct edwAnalysisStep *edwAnalysisStepLoadAll(char *fileName) 
/* Load all edwAnalysisStep from a whitespace-separated file.
 * Dispose of this with edwAnalysisStepFreeList(). */
{
struct edwAnalysisStep *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = edwAnalysisStepLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisStep *edwAnalysisStepLoadAllByChar(char *fileName, char chopper) 
/* Load all edwAnalysisStep from a chopper separated file.
 * Dispose of this with edwAnalysisStepFreeList(). */
{
struct edwAnalysisStep *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = edwAnalysisStepLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisStep *edwAnalysisStepCommaIn(char **pS, struct edwAnalysisStep *ret)
/* Create a edwAnalysisStep out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new edwAnalysisStep */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->softwareCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->software, ret->softwareCount);
for (i=0; i<ret->softwareCount; ++i)
    {
    ret->software[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->cpusRequested = sqlSignedComma(&s);
*pS = s;
return ret;
}

void edwAnalysisStepFree(struct edwAnalysisStep **pEl)
/* Free a single dynamically allocated edwAnalysisStep such as created
 * with edwAnalysisStepLoad(). */
{
struct edwAnalysisStep *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
/* All strings in software are allocated at once, so only need to free first. */
if (el->software != NULL)
    freeMem(el->software[0]);
freeMem(el->software);
freez(pEl);
}

void edwAnalysisStepFreeList(struct edwAnalysisStep **pList)
/* Free a list of dynamically allocated edwAnalysisStep's */
{
struct edwAnalysisStep *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    edwAnalysisStepFree(&el);
    }
*pList = NULL;
}

void edwAnalysisStepOutput(struct edwAnalysisStep *el, FILE *f, char sep, char lastSep) 
/* Print out edwAnalysisStep.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->softwareCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->softwareCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->software[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
fprintf(f, "%d", el->cpusRequested);
fputc(lastSep,f);
}


char *edwAnalysisRunCommaSepFieldNames = "id,jobId,experiment,analysisStep,configuration,tempDir,firstInputId,inputFileCount,inputFileIds,inputTypes,assemblyId,outputFileCount,outputNamesInTempDir,outputFormats,outputTypes,jsonResult,uuid,createStatus,createCount,createFileIds";

struct edwAnalysisRun *edwAnalysisRunLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all edwAnalysisRun from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with edwAnalysisRunFreeList(). */
{
struct edwAnalysisRun *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = edwAnalysisRunLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void edwAnalysisRunSaveToDb(struct sqlConnection *conn, struct edwAnalysisRun *el, char *tableName, int updateSize)
/* Save edwAnalysisRun as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. This function automatically escapes quoted strings for mysql. */
{
struct dyString *update = newDyString(updateSize);
char  *inputFileIdsArray, *inputTypesArray, *outputNamesInTempDirArray, *outputFormatsArray, *outputTypesArray, *createFileIdsArray;
inputFileIdsArray = sqlUnsignedArrayToString(el->inputFileIds, el->inputFileCount);
inputTypesArray = sqlStringArrayToString(el->inputTypes, el->inputFileCount);
outputNamesInTempDirArray = sqlStringArrayToString(el->outputNamesInTempDir, el->outputFileCount);
outputFormatsArray = sqlStringArrayToString(el->outputFormats, el->outputFileCount);
outputTypesArray = sqlStringArrayToString(el->outputTypes, el->outputFileCount);
createFileIdsArray = sqlUnsignedArrayToString(el->createFileIds, el->createCount);
sqlDyStringPrintf(update, "insert into %s values ( %u,%u,'%s','%s','%s','%s',%u,%u,'%s','%s',%u,%u,'%s','%s','%s','%s','%s',%d,%u,'%s')", 
	tableName,  el->id,  el->jobId,  el->experiment,  el->analysisStep,  el->configuration,  el->tempDir,  el->firstInputId,  el->inputFileCount,  inputFileIdsArray ,  inputTypesArray ,  el->assemblyId,  el->outputFileCount,  outputNamesInTempDirArray ,  outputFormatsArray ,  outputTypesArray ,  el->jsonResult,  el->uuid,  el->createStatus,  el->createCount,  createFileIdsArray );
sqlUpdate(conn, update->string);
freeDyString(&update);
freez(&inputFileIdsArray);
freez(&inputTypesArray);
freez(&outputNamesInTempDirArray);
freez(&outputFormatsArray);
freez(&outputTypesArray);
freez(&createFileIdsArray);
}

struct edwAnalysisRun *edwAnalysisRunLoad(char **row)
/* Load a edwAnalysisRun from row fetched with select * from edwAnalysisRun
 * from database.  Dispose of this with edwAnalysisRunFree(). */
{
struct edwAnalysisRun *ret;

AllocVar(ret);
ret->inputFileCount = sqlUnsigned(row[7]);
ret->outputFileCount = sqlUnsigned(row[11]);
ret->createCount = sqlUnsigned(row[18]);
ret->id = sqlUnsigned(row[0]);
ret->jobId = sqlUnsigned(row[1]);
safecpy(ret->experiment, sizeof(ret->experiment), row[2]);
ret->analysisStep = cloneString(row[3]);
ret->configuration = cloneString(row[4]);
ret->tempDir = cloneString(row[5]);
ret->firstInputId = sqlUnsigned(row[6]);
{
int sizeOne;
sqlUnsignedDynamicArray(row[8], &ret->inputFileIds, &sizeOne);
assert(sizeOne == ret->inputFileCount);
}
{
int sizeOne;
sqlStringDynamicArray(row[9], &ret->inputTypes, &sizeOne);
assert(sizeOne == ret->inputFileCount);
}
ret->assemblyId = sqlUnsigned(row[10]);
{
int sizeOne;
sqlStringDynamicArray(row[12], &ret->outputNamesInTempDir, &sizeOne);
assert(sizeOne == ret->outputFileCount);
}
{
int sizeOne;
sqlStringDynamicArray(row[13], &ret->outputFormats, &sizeOne);
assert(sizeOne == ret->outputFileCount);
}
{
int sizeOne;
sqlStringDynamicArray(row[14], &ret->outputTypes, &sizeOne);
assert(sizeOne == ret->outputFileCount);
}
ret->jsonResult = cloneString(row[15]);
safecpy(ret->uuid, sizeof(ret->uuid), row[16]);
ret->createStatus = sqlSigned(row[17]);
{
int sizeOne;
sqlUnsignedDynamicArray(row[19], &ret->createFileIds, &sizeOne);
assert(sizeOne == ret->createCount);
}
return ret;
}

struct edwAnalysisRun *edwAnalysisRunLoadAll(char *fileName) 
/* Load all edwAnalysisRun from a whitespace-separated file.
 * Dispose of this with edwAnalysisRunFreeList(). */
{
struct edwAnalysisRun *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[20];

while (lineFileRow(lf, row))
    {
    el = edwAnalysisRunLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisRun *edwAnalysisRunLoadAllByChar(char *fileName, char chopper) 
/* Load all edwAnalysisRun from a chopper separated file.
 * Dispose of this with edwAnalysisRunFreeList(). */
{
struct edwAnalysisRun *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[20];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = edwAnalysisRunLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct edwAnalysisRun *edwAnalysisRunCommaIn(char **pS, struct edwAnalysisRun *ret)
/* Create a edwAnalysisRun out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new edwAnalysisRun */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->jobId = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->experiment, sizeof(ret->experiment));
ret->analysisStep = sqlStringComma(&s);
ret->configuration = sqlStringComma(&s);
ret->tempDir = sqlStringComma(&s);
ret->firstInputId = sqlUnsignedComma(&s);
ret->inputFileCount = sqlUnsignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->inputFileIds, ret->inputFileCount);
for (i=0; i<ret->inputFileCount; ++i)
    {
    ret->inputFileIds[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->inputTypes, ret->inputFileCount);
for (i=0; i<ret->inputFileCount; ++i)
    {
    ret->inputTypes[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->assemblyId = sqlUnsignedComma(&s);
ret->outputFileCount = sqlUnsignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->outputNamesInTempDir, ret->outputFileCount);
for (i=0; i<ret->outputFileCount; ++i)
    {
    ret->outputNamesInTempDir[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->outputFormats, ret->outputFileCount);
for (i=0; i<ret->outputFileCount; ++i)
    {
    ret->outputFormats[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->outputTypes, ret->outputFileCount);
for (i=0; i<ret->outputFileCount; ++i)
    {
    ret->outputTypes[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->jsonResult = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->uuid, sizeof(ret->uuid));
ret->createStatus = sqlSignedComma(&s);
ret->createCount = sqlUnsignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->createFileIds, ret->createCount);
for (i=0; i<ret->createCount; ++i)
    {
    ret->createFileIds[i] = sqlUnsignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
*pS = s;
return ret;
}

void edwAnalysisRunFree(struct edwAnalysisRun **pEl)
/* Free a single dynamically allocated edwAnalysisRun such as created
 * with edwAnalysisRunLoad(). */
{
struct edwAnalysisRun *el;

if ((el = *pEl) == NULL) return;
freeMem(el->analysisStep);
freeMem(el->configuration);
freeMem(el->tempDir);
freeMem(el->inputFileIds);
/* All strings in inputTypes are allocated at once, so only need to free first. */
if (el->inputTypes != NULL)
    freeMem(el->inputTypes[0]);
freeMem(el->inputTypes);
/* All strings in outputNamesInTempDir are allocated at once, so only need to free first. */
if (el->outputNamesInTempDir != NULL)
    freeMem(el->outputNamesInTempDir[0]);
freeMem(el->outputNamesInTempDir);
/* All strings in outputFormats are allocated at once, so only need to free first. */
if (el->outputFormats != NULL)
    freeMem(el->outputFormats[0]);
freeMem(el->outputFormats);
/* All strings in outputTypes are allocated at once, so only need to free first. */
if (el->outputTypes != NULL)
    freeMem(el->outputTypes[0]);
freeMem(el->outputTypes);
freeMem(el->jsonResult);
freeMem(el->createFileIds);
freez(pEl);
}

void edwAnalysisRunFreeList(struct edwAnalysisRun **pList)
/* Free a list of dynamically allocated edwAnalysisRun's */
{
struct edwAnalysisRun *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    edwAnalysisRunFree(&el);
    }
*pList = NULL;
}

void edwAnalysisRunOutput(struct edwAnalysisRun *el, FILE *f, char sep, char lastSep) 
/* Print out edwAnalysisRun.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
fprintf(f, "%u", el->jobId);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->experiment);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->analysisStep);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->configuration);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tempDir);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->firstInputId);
fputc(sep,f);
fprintf(f, "%u", el->inputFileCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->inputFileCount; ++i)
    {
    fprintf(f, "%u", el->inputFileIds[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->inputFileCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->inputTypes[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
fprintf(f, "%u", el->assemblyId);
fputc(sep,f);
fprintf(f, "%u", el->outputFileCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->outputFileCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->outputNamesInTempDir[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->outputFileCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->outputFormats[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->outputFileCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->outputTypes[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->jsonResult);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->uuid);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->createStatus);
fputc(sep,f);
fprintf(f, "%u", el->createCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->createCount; ++i)
    {
    fprintf(f, "%u", el->createFileIds[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */
