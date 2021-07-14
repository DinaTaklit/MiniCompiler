# Mini Compiler

- This is a Compiler to Evaluate and generate Inetermediate Code For Arithmetique Operation, and also interpret the generated intermediate code. 
- The compiler also well handle errors.
- THe compiler is made with Flex and Bison.

## Setup

- To generate the exec file for both 2 parts: type this cmds in ur terminal with appropriate file name. 
```bash
bison -d yacc.y 

flex lex.l

gcc -std=c99 -o tp ccalc.c yacc.tab.c lex.yy.c -lm
```
- Theie is already an existing file which you could run by `./tp` command
- The code is well commented to understand code easily.
- A report in french lang is provided explaining in details the content of the this project.

Enjoy :D.
