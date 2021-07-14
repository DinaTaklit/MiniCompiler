#include "ccalc.h"
// To generate Quad  And put it in the file Out
extern void WriteQuad(char *opCode,char *src1,char *src2,char *dest)
{
  char *cmd=malloc(50);
  sprintf(cmd,"%s %s %s %s\n",opCode,src1,src2,dest);
  fputs(cmd,file);
  free(cmd);
  NumLine++;
}
//========================================================================
//Generate The Quad and tmp for Affectation
extern void AffQuad(char *dest,char *src)
{
        if(idIndex(dest,0)==-1){
         IDs[cptIDs].name=dest;
         cptIDs++;
        }
        WriteQuad("=",src,"#",dest); 
          
}
//=========================================================================
// Return -1 if it does not exist else it return the index of the ID
extern int idIndex(char * ID,int fromfile)
{
  int index=0;
  int stop=0;
  while((index<cptIDs)&& (!stop)){
    if (fromfile==0)
    {if(strcmp(IDs[index].name,ID))    
      index++;
      else 
      stop=1;
    }
    else 
    {
      if (strstr(ID,IDs[index].name) != NULL)
      stop=1;
      else 
        index++;
    }   
  }
  if(index<cptIDs){ return index; }
  return -1;
}
//========================================================================
// Verify if a string is numeric 
/* Link to the given function https://rosettacode.org/wiki/Determine_if_a_string_is_numeric **/
extern
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}
/**********************************************************************************/

/**********************Basic Arithmitic Operations***********************************/
//Add 2 numbers
extern
char* Add(char * a, char * b) {
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("+",a,b,Tmps[cptTmps].name);
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
//========================================================================
//Sub 2 numbers
extern
char* Sub(char * a, char * b) {
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("-",a,b,Tmps[cptTmps].name);
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
//========================================================================
//Multiplication
extern
char* Mul(char * a, char * b) {
   Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("*",a,b,Tmps[cptTmps].name);
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
//========================================================================
//Division
extern
char* Div(char * a, char * b) {
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("/",a,b,Tmps[cptTmps].name);
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
//========================================================================
//Sub Unaire
extern
char* SubU(char * a ) {
   Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("-",a,"#",Tmps[cptTmps].name);
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
//========================================================================
//Pow
  //Here the tric is to think like if we gonna generate assembler statment
  //The assembler code :
  /**
  1. = 1 dest
  2. Load b  
  3. Jz 7    //We gonna compare in every itteration b with zero 
  4. * dest a dest
  5. - b 1 b 
  6. jmp 2
  7. .....
  **/
extern
char* Pow(char * a, char * b) {
Tmps[cptTmps].name=malloc(12);
sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);//The tmp for the dest   

Tmps[cptTmps+1].name=malloc(12);
sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);

//We affecte the value  of the b to the generate tmp
WriteQuad("=",b,"#",Tmps[cptTmps+1].name);  

WriteQuad("=","1","#",Tmps[cptTmps].name);
WriteQuad("Load",Tmps[cptTmps+1].name,"#","#");
char *whereJmp=malloc(12);
sprintf(whereJmp,"%d",NumLine+5); // we are in the 2nd line and we need to jump the 7th line
WriteQuad("JZ","#","#",whereJmp);
//Maybe we need first to load the dest
WriteQuad("*",Tmps[cptTmps].name,a,Tmps[cptTmps].name);
WriteQuad("-",Tmps[cptTmps+1].name,"1",Tmps[cptTmps+1].name);
sprintf(whereJmp,"%d",NumLine-3); // we are in the 5 line and we need to jum to the 2nd line 
WriteQuad("JMP","#","#",whereJmp);
free(whereJmp);
cptTmps=cptTmps+2;
return Tmps[cptTmps-2].name;
}
/**********************************************************************************/
/**  
Resouce of the resource code https://www.quora.com/How-do-I-write-a-program-for-finding-the-square-root-of-a-number-without-using-the-sqrt-function
**/
  /*float m,n;
 float num;
 n=0.0001;   // This is taken small so that we can calculate upto decimal places also
 printf("ENTER A NUMBER : ");
 scanf("%f",&num);
 
 for(m=0;m<num;m=m+n)
 {
   if((m*m)>num)
   {
   m=m-n;         // This if() is used to calculate the final value as soon as the square of the number exceeds
   break;      //  the number then we deduct the value exceeded and stop the procedure using break; this is our final value which is stored in m;
   } 
  }*/
extern char* Sqrt(char * a){
Tmps[cptTmps].name=malloc(12);
sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);//tmp1=>dest
WriteQuad("=","0","#",Tmps[cptTmps].name); 
Tmps[cptTmps+1].name=malloc(12);//tmp2
sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);
WriteQuad("=","0.0001","#",Tmps[cptTmps+1].name); 
Tmps[cptTmps+2].name=malloc(12);
sprintf(Tmps[cptTmps+2].name,"tmp%d",cptTmps+3);
//La bucle tanque
WriteQuad("-",Tmps[cptTmps].name,a,Tmps[cptTmps+2].name);
WriteQuad("Load",Tmps[cptTmps+2].name,"#","#");
char *tmp=malloc(12);
sprintf(tmp,"%d",NumLine+10);
WriteQuad("JG","#","#",tmp);//Jmp La fin
free(tmp);
WriteQuad("*",Tmps[cptTmps].name,Tmps[cptTmps].name,Tmps[cptTmps+2].name);
WriteQuad("-",Tmps[cptTmps+2].name,a,Tmps[cptTmps+2].name);
tmp=malloc(12);
sprintf(tmp,"%d",NumLine+5);
WriteQuad("Load",Tmps[cptTmps+2].name,"#","#");
WriteQuad("JG","#","#",tmp);//JMP to -
free(tmp);
WriteQuad("+",Tmps[cptTmps].name,Tmps[cptTmps+1].name,Tmps[cptTmps].name);
tmp=malloc(12);
sprintf(tmp,"%d",NumLine-7);//without load 5
WriteQuad("JMP","#","#",tmp);//JMP to first -
WriteQuad("-",Tmps[cptTmps].name,Tmps[cptTmps+1].name,Tmps[cptTmps].name);
tmp=malloc(12);
sprintf(tmp,"%d",NumLine+2);
WriteQuad("JMP","#","#",tmp); //Jmp tp fin 
free(tmp);
cptTmps=cptTmps+3;
return Tmps[cptTmps-3].name;
}
 
/*************************Another Operations***************************************/
extern char* Sum( char* values[50],int cpt)
{
  int i=0;
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("=",values[i],"#",Tmps[cptTmps].name);
  for (i=1;i<cpt;i++)
  {
    WriteQuad("+",Tmps[cptTmps].name,values[i],Tmps[cptTmps].name);
  }
  cptTmps++;
  return Tmps[cptTmps-1].name;
}
/**************************************************************************************/
extern 
char* Moy( char* values[50],int cpt)
{
  char *tmp;
  tmp=malloc(12);
  sprintf(tmp,"%d",cpt);
  //It's a same as Som here we just divide by cpt
  Sum(values,cpt);
  WriteQuad("/",Tmps[cptTmps-1].name,tmp,Tmps[cptTmps-1].name);
  cptTmps++;
  return Tmps[cptTmps-2].name;
}
/***************************************************************************************/
extern
char* Variance( char* values[15],int cpt) {
  //vriance (n1,n2,n3,...,n)=(carré(n1-moy(n1...n))+carré(n2-moy(n2....n))+....)/n-1

  //float moy=ReduceMoy(values,cpt);
   Moy(values,cpt); // tmp2=Tmps[cptTmps-2].name contient la valeur

  //float variance=0;
  Tmps[cptTmps].name=malloc(12);//tmp3
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("=","0","#",Tmps[cptTmps].name);
  //Tmp pour la soustraction et la multiplication
  Tmps[cptTmps+1].name=malloc(12);//tmp4
  sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);

    for (int j=0;j<cpt;j++)
    {
      //variance+=pow((values[j]-moy),2);=> tmp4=(value[j]-tmp2). tmp3=tmp4*tmp4
      WriteQuad("-",values[j],Tmps[cptTmps-2].name,Tmps[cptTmps+1].name);
      WriteQuad("*",values[j],Tmps[cptTmps+1].name,Tmps[cptTmps+1].name);
      WriteQuad("+",Tmps[cptTmps+1].name,Tmps[cptTmps].name,Tmps[cptTmps].name);    
    }
    //return (variance/(cpt-1));
    //tmp3=tmp3/cpt-1
    char * tmp=malloc(12);
    sprintf(tmp,"%d",cpt); //Sicnce all src off Write Quad are char * we cant put cpt-1 which is int directly
    WriteQuad("/",Tmps[cptTmps].name,tmp,Tmps[cptTmps].name);
    free(tmp);
    cptTmps=cptTmps+2;
  return Tmps[cptTmps-2].name;
}
/***************************************************************************************/
extern char* ecrt( char* values[15],int cpt){
  //return (sqrt(Var( values,cpt)));
  Variance(values,cpt);
  Sqrt(Tmps[cptTmps-2].name);
  return Tmps[cptTmps-3].name;
}
/***************************************************************************************/
extern char *Max(char* values[50],int cpt)
{
  int i=0;
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("=",values[i],"#",Tmps[cptTmps].name); //tmp1 contien la valeur du max
  Tmps[cptTmps+1].name=malloc(12);
  sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);
  Tmps[cptTmps+2].name=malloc(12);
  sprintf(Tmps[cptTmps+2].name,"tmp%d",cptTmps+3);
  for (i=1;i<cpt;i++)
  {
    WriteQuad("=",values[i],"#",Tmps[cptTmps+1].name);// = tab[i] tmp2
    WriteQuad("-",Tmps[cptTmps].name,Tmps[cptTmps+1].name,Tmps[cptTmps+2].name);//Sub tmp1 tmp2 tmp3
    
    WriteQuad("Load",Tmps[cptTmps+2].name,"#","#");
    char *tmp=malloc(12);
    sprintf(tmp,"%d",NumLine+3);//il faut jumper a =[i]  tmp2
    WriteQuad("JG","#","#",tmp);
    WriteQuad("=",Tmps[cptTmps+1].name,"#",Tmps[cptTmps].name);// = tmp2 tmp1
    free(tmp);
  }
  cptTmps=cptTmps+3;
  return Tmps[cptTmps-3].name;
}
/***************************************************************************************/

/***************************************************************************************/
extern char *Min(char* values[50],int cpt)
{
  int i=0;
  Tmps[cptTmps].name=malloc(12);
  sprintf(Tmps[cptTmps].name,"tmp%d",cptTmps+1);
  WriteQuad("=",values[i],"#",Tmps[cptTmps].name); //tmp1 contien la valeur du max
  Tmps[cptTmps+1].name=malloc(12);
  sprintf(Tmps[cptTmps+1].name,"tmp%d",cptTmps+2);
  Tmps[cptTmps+2].name=malloc(12);
  sprintf(Tmps[cptTmps+2].name,"tmp%d",cptTmps+3);
  for (i=1;i<cpt;i++)
  {
    WriteQuad("=",values[i],"#",Tmps[cptTmps+1].name);// = tab[i] tmp2
    WriteQuad("-",Tmps[cptTmps].name,Tmps[cptTmps+1].name,Tmps[cptTmps+2].name);//Sub tmp1 tmp2 tmp3
    
    WriteQuad("Load",Tmps[cptTmps+2].name,"#","#");
    char *tmp=malloc(12);
    sprintf(tmp,"%d",NumLine+3);//il faut jumper a =[i]  tmp2
    WriteQuad("JL","#","#",tmp);
    WriteQuad("=",Tmps[cptTmps+1].name,"#",Tmps[cptTmps].name);// = tmp2 tmp1
    free(tmp);
  }
  cptTmps=cptTmps+3;
  return Tmps[cptTmps-3].name;
}
/***************************************************************************************/