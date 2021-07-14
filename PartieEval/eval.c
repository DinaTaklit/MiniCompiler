/**
This file contains all the functions of the project
**/

#include <math.h>
#include "ccalc.h"
///define max and min function 
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)




//================================================================
extern float SI(float values[15])
{
 if (values[0]==1)
 {
  return values[1];
 }
 else 
  return values[2];
}
//================================================================
extern
float Ecrt( float values[15],int cpt) {
  return (sqrt(Var( values,cpt)));
}
//============================Variance======================================
extern
float Var( float values[15],int cpt) {
  //vriance (n1,n2,n3,...,n)=(n1-moy(n1...n)carré+n2-moy(n2....n)carré+....))/n-1
  float variance=0;
  float moy=Moy(values,cpt);
    for (int j=0;j<cpt;j++)
       variance+=pow((values[j]-moy),2);
  return (variance/(cpt));
}



//--------------------------------------------------------------------
 // Moy Return the Average for the values given in the array values

extern 
float Moy( float values[15],int cpt)
{
   float moy=0;
            moy = (Sum(values,cpt)/cpt);
   return moy;
}
//==============================================================
//Sum up all the values of the given array
extern 
float Sum( float values[15],int cpt)
{
   float som=0;
               for (int j=0;j<cpt;j++)
                som+=values[j];
   return som;
}
//====================Max of list of numbers======================
extern 
float Max( float values[15],int cpt)
{
   float max=0;
               for (int j=0;j<cpt;j++)
                max=MAX(values[j],max);
   return max;
}
//====================Min of list of numbers======================
extern 
float Min(float values[15],int cpt)
{
     float min=values[0];
               for (int j=0;j<cpt;j++)
                min=MIN(values[j],min);
    return min;
}
//==========================Pow=====================================
extern
float Pow(float a, float b) {
  return pow(a,b);
}
//===================================================================
//Add 2 numbers
extern 
float Add(float a, float b) {
  return a + b;
}
//-------------------------------------------------------------------
//sub two numbers
extern
float Sub(float a, float b) {
  return a - b;
}
//===================================================================
//multiply two numbers
extern
float Mult(float a, float b) {
  return a * b;
}
//==================================================================
//divide two numbers, check for zero
extern
float Div(float a, float b, YYLTYPE *bloc) {
  if (  b == 0  ) {
 PrintError("division by zero! Line %d:c%d to %d:c%d",
                        bloc->first_line, bloc->first_column,
                        bloc->last_line, bloc->last_column);
    return FLT_MAX;
  }
  return a / b;
}
//--------------------------------------------------------------------
