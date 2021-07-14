/*bison -d yacc.y 
flex lex.l
gcc -o tp ccalc.c yacc.tab.c lex.yy.c -lm
gcc -std=c99 -o tp ccalc.c yacc.tab.c lex.yy.c -lm
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
  char *string;//refers to Tmps or Identifier
  int fcc; //The function : som, moy,max, min...
  struct { // Struct of list
    char * values[50];
    int cpt;
 } list;
}

%token <string>   IDENTIFIER
%token <v> nb 
%type <string> E fct
%token <fcc> fc
%type <list> L
%type <fcc> nf

%left '+' '-'
%left '*' '/'
%right '^'
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
    : IDENTIFIER  ':' E
      {
         IDGet($1, &@1);
        AffQuad($1,$3);
      }
      | E { }
    ;

  E    
       :   E '+' E   {
        $$= Add($1,$3);
       }
       | E '-' E    {
        $$ = Sub($1, $3);
       }
       |   E '*' E    {
        $$ = Mul($1, $3);
       }
       |   E '/' E    {
        $$ = Div($1, $3);
       }
       |   '-' E     %prec moins_unaire 
        {$$=SubU($2);}
       | '(' E ')'   {$$=$2;}
       | E '^' E 
        {
            //We have first to ensure that b is a degit 
           // printf("isNumeric($3) %d\n",isNumeric($3) );              
           // if (isNumeric($3))  
              $$=Pow($1,$3);//Generate the Quad of Pow   
            //else  
             // printf("The given base is not a number\n");              
        }

       |   nb        {
          char * tmp=malloc(12);
          sprintf(tmp,"%f",$1);
          $$=tmp;
       }
       | fct       
        {
          $$=$1;
        }
       | IDENTIFIER
       {
          IDGet($1, &@1);
        if(idIndex($1,0)==-1){
              yyerror("Identifier not initialized"); return -1;}
              else{
                $$=$1;
              }
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
               $$=Variance($3.values,$3.cpt);   
          break;  
          case 6:
               $$=ecrt($3.values,$3.cpt);   
          break;  
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
// a more sophisticated error-function
  PrintError(s);
}

