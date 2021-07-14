
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

// Functions of TP
extern float SI(float values[15]);
extern float Ecrt(float [15],int);
extern float Var(float [15],int);
extern float Moy(float [15],int);
extern float Sum(float [15],int);
extern float Max(float [15],int);
extern float Min(float [15],int);
extern float Pow(float, float);
extern float Add(float, float);
extern float Sub(float, float);
extern float Mult(float, float);
extern float Div(float, float, YYLTYPE*);

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
