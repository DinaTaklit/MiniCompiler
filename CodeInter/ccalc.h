
#ifndef CCALC_H_
#define CCALC_H_

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include "yacc.tab.h"

// Functions of lex & yacc
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(char*);


typedef struct _Variable {
  char    *name;
  float  value;
} Variable;

//Local Varaible
static FILE *file;//Le fichier dont on va ecrire le code intermédiare
//static char * Tmps[200];//contains all generated tmp tmps of sys
//static char * IDs[100]; //Contains all IDs 
static Variable Tmps[200];//contains all generated tmp tmps of sys
static Variable IDs[100]; //Contains all IDs 
static int cptIDs; // Cpt of IDs tab
static int cptTmps;//to browse the Tmps table
static int NumLine;//The cuurent line in the ouput file we will need it espacialy for the function that generate Jump instruction 
//static Variable vars[MAXVARS];
static char* Lines[300];//Contains all the lines of Output for the evaluation 
static char *ValuesTab[50];//We consider that a table reseved in memory for that.



/*
 * lex & yacc
 */
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(char*);

///The void of intermediate code
extern void WriteQuad(char *opCode,char *src1,char *src2,char *dest);
extern void AffQuad(char *dest,char * src);
extern int idIndex(char * ID,int fromFile);//Get the index of the identifier 
extern int isNumeric (const char * s); // Check if the givern string is numeric
extern int getIndexVar(char *dest); // To get the index of the variable
extern float getValueVar(char *a);// To get the value of the given variable
extern void CopierTab(char *values[50],int cpt);//We concider that it gonna generate a table
/**************************************************************************************/
extern char* nbTmp(char * src);
extern char* Add(char * a, char * b);
extern char* Sub(char * a, char * b);
extern char* Mul(char * a, char * b);
extern char* Div(char * a, char * b);
extern char* SubU(char * a);
extern char* Pow(char * a,char *b);
//=============================Another Option=============================================
extern char* Sum( char* values[50],int cpt);
extern char* SumV2( char* values[50],int cpt);
extern char* Moy( char* values[50],int cpt);
extern char* Max(char* values[50],int cpt);
extern char *Min(char* values[50],int cpt);
extern char* Variance( char* values[15],int cpt);
extern char* ecrt( char* values[15],int cpt);
//========================================================================================
extern void evluate (int NbLine);
extern void  Display();
extern void EvaluateAff(char *src,char* dest);
//========================================================================================
extern void EvaluateAdd(char *a, char *b,char * dest);
extern void EvaluateSub(char *a, char *b,char * dest);
extern void EvaluateMul(char *a, char *b,char * dest);
extern void EvaluateDiv(char *a, char *b,char * dest);
extern void EvaluateSubU(char *a,char * dest);
//========================================================================================
extern float EvaluateLoad(char *src);
extern int EvaluateJZ(float a,char *dest);
extern int EvaluateJG(float a,char *dest);
extern int EvaluateJL(float a,char *dest);
//=========================================================================================
//Need it for the final display and to print significant errors
extern void DisplayLine(void);
extern int GetNextChar(char *b, int maxBuffer);
extern void BeginToken(char*);
extern void PrintError(char *s, ...);

//To manipulate the deferent IDs
extern Variable *IDGet(char*, YYLTYPE*);
extern void IDsetValue(Variable*, float);
extern float IDGetValue(char*, YYLTYPE*);
extern void DisplayAllIDs();

#endif /*CCALC_H_*/
