#include "ccalc.h"
/************************************************************************************/
/************************************************************************************/
extern void evluate (int Nbline)
{

  int c;
  FILE *file2;
  file2 = fopen("out.txt", "r");
  float LoadValue;
  int indexLine=0;
  int i=0; 

  char lin[256];
  int Nbl=Nbline ;
  if (file2) {
      //Puts all the line of the file in the table
     while (fgets(lin, sizeof(lin), file2)!=NULL)
      {
        Lines[i]=malloc(256);
        sprintf(Lines[i],"%s",lin);
        i++;
      }
   
    i=0;    
    while (i<Nbl)
    {
        char *array[5];
        int j=0;
        char *tmp=malloc(256);
        sprintf(tmp,"%s",Lines[i]);
        array[j] = strtok(tmp," ");
        while(array[j]!=NULL)
        {
           array[++j] = strtok(NULL," ");
        }
        if (strcmp(array[0],"+")==0)
        {
          EvaluateAdd(array[1],array[2],array[3]);
          i++;
        } 
        else if (strcmp(array[0],"-")==0)
        {
          if (strstr(array[2],"#")!=NULL)
           EvaluateSubU(array[1],array[3]);
          else
          EvaluateSub(array[1],array[2],array[3]);
         i++;
        } 
         else if (strcmp(array[0],"*")==0)
        {
          EvaluateMul(array[1],array[2],array[3]);
          i++;
        } 
         else if (strcmp(array[0],"/")==0)
        {
          EvaluateDiv(array[1],array[2],array[3]);
          i++;
        } 
        else if (strcmp(array[0],"Load")==0)
        {
           LoadValue=EvaluateLoad(array[1]);
           i++;
        } 


        else if (strcmp(array[0],"JZ")==0)
        {
           indexLine= EvaluateJZ(LoadValue,array[3]);
           if( indexLine==-1)
              i=i+1; //cause i begin with 0    
          else 
            i=indexLine-1;/*we jump to the given line and because 
            it start from 0 so we sub 1*/
        }

        //======================================================
          else if (strcmp(array[0],"JG")==0)
        {
           indexLine= EvaluateJG(LoadValue,array[3]);
           if( indexLine==-1)
            {
              i=i+1; //cause i begin with 0
            }
          else 
          {
            i=indexLine-1;//we jump to the given line and because it start from 0 so we sub 1
          }
        }
        //===================================================
          else if (strcmp(array[0],"JL")==0)
        {
           indexLine= EvaluateJL(LoadValue,array[3]);
           if( indexLine==-1)
            {
              i=i+1; //cause i begin with 0
            }
          else 
          {
            i=indexLine-1;//we jump to the given line and because it start from 0 so we sub 1
          }
        }
        //===================================================
        else if (strcmp(array[0],"JMP")==0)
        {
          i=atoi(array[3])-1;//cause i begin from 0
        }
        else if (strcmp(array[0],"JG")==0)
        {
          i=atoi(array[3])-1;//cause i begin from 0
        }
       else if (strcmp(array[0],"=")==0)
       {
          EvaluateAff(array[1],array[3]);
          i++;
       }
       free(tmp);
    }
    fclose(file2);
  }
}
//======================================================================
extern void EvaluateAff(char *src,char* dest)
{
    float num1=getValueVar(src);
    int index=getIndexVar(dest);
    if (strstr(dest,"tmp") != NULL) {
      Tmps[index].value=num1;
    }
    else
    {
      IDs[index].value=num1;
    } 
}
//========================================================================
/******************** EvaluateArithmetic Ops********************************/
extern
void EvaluateAdd(char *a, char *b,char * dest)
{
    float num1=getValueVar(a);
    float num2= getValueVar(b);
    int index=getIndexVar(dest);
     Tmps[index].value=num1+num2;
}
//========================================================================
extern
void EvaluateSub(char *a, char *b,char * dest)
{
    float num1=getValueVar(a);
    float num2= getValueVar(b);
    int index=getIndexVar(dest);
    Tmps[index].value=num1-num2;
}
//========================================================================
extern
void EvaluateMul(char *a, char *b,char * dest)
{
    float num1=getValueVar(a);
    float num2= getValueVar(b);
    int index=getIndexVar(dest);
    Tmps[index].value=num1*num2;
}
//========================================================================
extern
void EvaluateDiv(char *a, char *b,char * dest)
{
    float num1=getValueVar(a);
    float num2= getValueVar(b);
    int index=getIndexVar(dest);
    Tmps[index].value=num1/num2;
}
//========================================================================
extern
void EvaluateSubU(char *a,char * dest)
{
    float num1=getValueVar(a);
    int index=getIndexVar(dest);
    Tmps[index].value=-num1;
}
//========================================================================
//========================================================================
extern float EvaluateLoad(char *src)
{
  return (getValueVar(src));
}
//========================================================================
extern int EvaluateJZ(float a,char *dest)
{
  int indexLine=0;
  if (a==0)
      indexLine=atoi(dest);
  else     
  indexLine=-1;
  return indexLine;
}
//========================================================================
//========================================================================
extern int EvaluateJG(float a,char *dest)
{
  int indexLine=0;
  if (a>=0)
  {
      indexLine=atoi(dest);
  }
  else     
  indexLine=-1;
  return indexLine;
}
//========================================================================
//========================================================================
extern int EvaluateJL(float a,char *dest)
{
  int indexLine=0;
  if (a<=0)
  {
      indexLine=atoi(dest);
  }
  else     
  indexLine=-1;
  return indexLine;
}
//========================================================================
extern float getValueVar(char *a)
{
  float num1;
  int index;
  if (strstr(a,"index") != NULL) {
            printf("getValueVar b %s\n",a);
            char *array[5];
            int i=0;
            array[i] = strtok(a,"index");//T get the tmp that contain the index of table Values
            printf("getValueVar array[0]%s\n",array[0]);
            int newIndex=getValueVar(array[0]);//Get the content of the tmp
            char *tmp=malloc(12);
            sprintf(tmp,"%s",ValuesTab[newIndex]);//here is the content of ValuesTab
            num1=getValueVar(tmp);
            free(tmp);
          }
  else if (strstr(a,"tmp") != NULL) {
            index=getIndexVar(a);
            num1=Tmps[index].value;
          }
 else if(isNumeric(a))
  num1= atof(a);
 else //Its an identifier 
 {
    int idIndx=idIndex(a,1);
    num1=IDs[idIndx].value;
 } 
return num1;
}
//========================================================================
extern int getIndexVar(char *dest)
{
   int index=0;
   if (strstr(dest, "tmp") != NULL)
   {
    char *array[5];
    int i=0;
    array[i] = strtok(dest,"tmp");
    index= (atoi(array[0]))-1;
   }
   else  //It's a variable
   {
      index=idIndex(dest,1);
   }
   return index;
}
//===========================================================================
extern void Display()
{
  printf(" The content of all the idetifiers :\n");
  int i=0;
  for (i = 0; i < cptIDs; i++)
  {
    printf(" %s= %f\n",IDs[i].name,IDs[i].value );
  }
}

//===========================================================================