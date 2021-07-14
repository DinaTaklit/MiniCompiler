%option noyywrap
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include "ccalc.h"
  #include "yacc.tab.h"

  #define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }
%}
ID [_a-zA-Z][_a-zA-Z0-9]*
%%
som {yylval.fcc=1; return fc;}
moy {yylval.fcc=2; return fc;}
min {yylval.fcc=3; return fc;}
max {yylval.fcc=4; return fc;}
var {yylval.fcc=5; return fc;}
ecr {yylval.fcc=6; return fc;}
SI {yylval.fcc=7;return fc;}

[0-9]+|[0-9]*\.[0-9]+ {
  BeginToken(yytext);
  yylval.v=atof(yytext);return nb;
}

{ID} {
    BeginToken(yytext);
    yylval.string = malloc(strlen(yytext)+1);
    strcpy(yylval.string, yytext);
    return IDENTIFIER;
    }
[ \t\r\n]+ {
        /* eat up whitespace */
        BeginToken(yytext);
        }
. { BeginToken(yytext);
      return yytext[0];}
%%
