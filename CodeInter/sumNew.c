/**Some if we consider that the table exst in data**/
extern 
char* Sum( char* values[50],int cpt)
{
  /** Assembler code
  1. Mov 0 des 
  2. Load cpt 
  3. JZ
  4. ADD dest tab[cpt-1] // Au cas ou on considère que le tableau est dans la mer
  5. Sub 1 cpt
  6.jump 2 
  7. ....
  **/

  char *tmp;
  char *tmp1;
  char *tmp2;
  tmp=malloc(12);
  tmp1=malloc(12);
  tmp2=malloc(12);

  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);

  Tmps[cptTmps+1].name=malloc(12);
  sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);

   sprintf(tmp,"%d",cpt);
   WriteQuad("Mov",tmp,"#",Tmps[cptTmps+1].name);
  
   WriteQuad("Mov","0","#",Tmps[cptTmps].name);
   WriteQuad("Load",Tmps[cptTmps+1].name,"#","#");
   sprintf(tmp1,"%d",NumLine+5);
   WriteQuad("JZ","#","#",tmp1);
   
   WriteQuad("+",Tmps[cptTmps].name,values[cpt-1],Tmps[cptTmps].name);
   WriteQuad("-",Tmps[cptTmps+1].name,"1",Tmps[cptTmps+1].name);
   sprintf(tmp2,"%d",NumLine-3);
   WriteQuad("JMP","#","#",tmp2);
   free(tmp); free(tmp1); free(tmp2); 
   cptTmps=cptTmps+2;
   return Tmps[cptTmps-2].name;
}