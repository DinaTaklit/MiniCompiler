# CompileEvaluateAndInetermediateCodeForArithmetiqueOperation
This file contains a very useful code  to evaluate arithmetic operation and generate the intermediate code for them and also interpret this intermediate code.Thes with best error handling.Hope it gonna help.
Made with Flex and Bison

To generate the exec file for both 2 parts
type this cmds on ur terminal and do not forget to enter in the appropriate file. 
Theie is already an existing file which u could run typing on ./tp

bison -d yacc.y 
flex lex.l
gcc -std=c99 -o tp ccalc.c yacc.tab.c lex.yy.c -lm

The code is well commented so it's easy to understand it.
And for those that understand the french language the report explains on details the content of the this project.
So that and i really hope that give a push to well understand how does the compiler function.
