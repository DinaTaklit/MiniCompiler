/*
//To coplile the given file
bison -d yacc.y 
flex lex.l
gcc -o tp ccalc.c yacc.tab.c lex.yy.c -lm
gcc -std=c99 -o tp ccalc.c yacc.tab.c lex.yy.c -lm
*/
/*
The first Bison feature of interest, hidden deep in the Bison manuals, is that it is possible to generate more meaningful error messages in case of a syntax error by using the macro YYERROR_VERBOSE.
The plain 'syntax error' message becomes:
Error 'syntax error, unexpected IDENTIFIER, expecting SEMICOLON'
This message is much better for debugging.
*/

%{
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccalc.h"
#define YYERROR_VERBOSE 1
static Variable *ID;//Global variable
%}

%defines

%union {
  float v; // The float values
  char *string;//refers to IDs
  int fcc; //The function : som, moy,max, min...

  struct { // Struct of list
  //float value;
    float values[15];
  int cpt;
 } list;
}
%token <v> nb
%token <string>   IDENTIFIER
%token <fcc> fc
%type <v> E fct
%type <list>L
%type <fcc> nf

%left '-' '+'
%left '*' '/'
%right '^'
%left '>' '<' '='
%right moins_unaire

%start program // to start with production program it's facultatif
%%
//Rules

program 
    : statement ';' program
    | statement ';'
    | statement error ';' program
      {
      yyerrok;
      }
    ;

    statement
    : IDENTIFIER
      {
        ID = IDGet($1, &@1);
      }
     ':' E
      {
        IDsetValue(ID, $4);
      }
      | E
    ;

  E    :   E '-' E    {
        $$ = Sub($1, $3);
       }
       |   E '+' E   {
         $$ = Add($1, $3);
       }
       |   E '*' E    {
        $$ = Mult($1, $3);
       }
       |   E '/' E    {
        $$ = Div($1, $3, &@3);
       }
       |   E '^' E   {$$=Pow($1, $3);}
       |   E '>' E   {
        if($1>$3) $$=1;
        else 
          $$=0;

       }
       | E '<' E   {
        if($1<$3) $$=1;
        else 
          $$=0;
       }
       | E '=' E   {
        if($1=$3) $$=1;
        else 
          $$=0;
       }

       |   '-' E     %prec moins_unaire  {$$=-$2;}
       | '(' E ')'   {$$=$2;}
       |   nb        {$$=$1;}
       |   fct       {$$=$1;}
       | IDENTIFIER
       {
        $$ = IDGetValue($1, &@1);
       }
       ;
       fct: nf '(' L ')'
       {
        switch($1)
        {
          case 1:
               $$=Sum($3.values,$3.cpt);    
          break;
          case 2:
               $$=Moy($3.values,$3.cpt); 
          break;
          case 3:
               $$=Min($3.values,$3.cpt);    
          break;
          case 4:              
               $$=Max($3.values,$3.cpt); 
          break;
          case 5:
              $$=Var($3.values,$3.cpt); 
          break;
          case 6:
              $$=Ecrt($3.values,$3.cpt); 
          break;
          case 7:
             $$= SI($3.values);
        }

       }
       ;
       nf : fc {
        $$=$1;

       }
       ;
       L    :   L ',' E {
            $$=$1; $$.values[$$.cpt++]=$3;

        }
       | E {
       $$.values[0]=$1;  $$.cpt=1;}
       ;
%%

extern
void yyerror(char *s) {
//  a more sophisticated error-function
  PrintError(s);
}

