
#include "ccalc.h"
#include "eval.c"

#define true 1
#define false 0


//T manipulate all the identifiers of the system

#define MAXIDs 100 
static Variable IDs[MAXIDs]; //Contains the identifiers
static int cptIDs=0; //To get the total IDs used

 
static FILE *file;
static int NumLine = 0;
static int eof = 0;

static int cptBuffer = 0;
static int BufferSize = 0;//Used to display the errors 
//Used to positionate the error
static int StartToken = 0;
static int TokenSize = 0;
static int NextStartToken = 0;

static int MaxBuff = 1000;
static char *buffer;

//====================================================================
//Display the content of Line
extern
void DisplayLine(void) {
  if (  NumLine != 0  ) 
   fprintf(stdout, "%6d |%.*s", NumLine, BufferSize, buffer);
}
//====================================================================
//Sofisticated Version of print Error
extern
void PrintError(char *errorstring, ...) {
  static char errmsg[10000];
  va_list args;
  int start=StartToken;
  int end=start + TokenSize - 1;
  int i;
  if (  eof  ) {
    fprintf(stdout, "...... !");
    for (i=0; i<BufferSize; i++)
      fprintf(stdout, ".");
    fprintf(stdout, "^-EOF\n");
  }
  else {
    fprintf(stdout, "\n...... !");
    for (i=1; i<start; i++)
      fprintf(stdout, ".");
    for (i=start; i<=end; i++)
      fprintf(stdout, "^");
    for (i=end+1; i<BufferSize; i++)
      fprintf(stdout, ".");
    fprintf(stdout, "   token%d:%d\n", start, end);
  }
  //print it using variable arguments :
  va_start(args, errorstring);
  vsprintf(errmsg, errorstring, args);
  va_end(args);
  fprintf(stdout, "Error: %s\n", errmsg);
}
//===================================================================
static
int getNextLine(void) {
  int i;
  char *p;
  cptBuffer = 0;
  StartToken = -1;
  NextStartToken = 1;
  eof = false;

  p = fgets(buffer, MaxBuff, file);
  if (  p == NULL  ) {
    if (  ferror(file)  )
      return -1;
    eof = true;
    return 1;
  }
  NumLine += 1;//To display the error
  BufferSize = strlen(buffer);
  DisplayLine();
  return 0;
}
//====================================================================
//reads a character from input for flex
extern
int GetNextChar(char *b, int maxBuffer) {
  int isNextLine;
  if (  eof  )
    return 0;
  //read next line if at the end of the current 
  while (  cptBuffer >= BufferSize  ) {
    isNextLine = getNextLine();
    if (  isNextLine != 0  )
      return 0;
    }
  /* ok, return character ------------------------------------------*/
  b[0] = buffer[cptBuffer];
  cptBuffer += 1;
  return b[0]==0?0:1;
}
//====================================================================
//Mark the beginig of new token
extern
void BeginToken(char *t) {
  /* remember last read token --------------------------------------*/
  StartToken = NextStartToken;
  TokenSize = strlen(t);
  NextStartToken = cptBuffer; // + 1;
  /* location for bison --------------------------------------------*/
  yylloc.first_line = NumLine;
  yylloc.first_column = StartToken;
  yylloc.last_line = NumLine;
  yylloc.last_column = StartToken + TokenSize - 1;
}
//===================================================================

//=================================================================
//simple search for a variable
static
Variable *findID(char *IDname) {
  int i;
  if (  IDname == NULL  )
    return NULL;
  for (i=0; i<cptIDs; i++)
    if (  strcmp(IDs[i].name, IDname) == 0  )
      return IDs+i;
  return NULL;
}
//===================================================================
//Add the given variable to the table of IDs
static
Variable *addID(char *IDname) {

  if (  IDname == NULL  )
    return NULL;
  if (  cptIDs >= MAXIDs  ) {
    PrintError("maximum number (%d) of variables reached", MAXIDs);
    return NULL;
  }
  IDs[cptIDs].value = 0;
  IDs[cptIDs].name = malloc(strlen(IDname)+1);
  if (  IDs[cptIDs].name == NULL  ) {
    PrintError("Error creating variable '%s'", IDname);
    return NULL;
  }
  strcpy(IDs[cptIDs].name, IDname);
  cptIDs += 1;
  return IDs+cptIDs-1;
}
//=====================================================
//gets a variable for reference, create if necessary
extern
Variable *IDGet(char *IDname, YYLTYPE *bloc) {
  Variable *var;
  var = findID(IDname);
  if (  var == NULL  )
    var = addID(IDname);
  return var;
}
//===================================================================
//Set the value to the ID
extern
void IDsetValue(Variable *ID, float value) {
  if (  ID == NULL  )
    return;
  ID->value = value;
}
//*****************************************************************
//Get the value of the given ID
extern
float IDGetValue(char *IDname, YYLTYPE *bloc) {
  Variable *ID = NULL;
  ID = findID(IDname);
  if (  ID == NULL  ) {
    PrintError("Reference to unknown variable '%s'",ID);
    ID = addID(IDname);
    if (  ID == NULL  )
      return 0;
  }
  return ID->value;
}
//===================================================================
//Display Variables
extern
void DisplayAllIDs() {
  int i;
  printf("%s ID------------------ Value----------\n","  ");
  for (i=0; i<cptIDs; i++)
    printf("%s '%-19.19s' %g\n","  ",
                        IDs[i].name, IDs[i].value);
  return;
}
//=====================================================================

extern
int main() {
  //int i;
  char *infile=NULL;
  printf("======================== Evaluation ======================== \n\n");
  infile = "in.txt";
  file = fopen(infile, "r");
  if (  file == NULL  ) {
    printf("cannot open input\n");
    return 12;
    }
  buffer = malloc(MaxBuff);
  if (  buffer == NULL  ) {
    printf("cannot allocate %d bytes of memory\n", MaxBuff);
    fclose(file);
    return 12;
  }
  DisplayLine();//Display the read line
  if (  getNextLine() == 0  )
    yyparse();
  free(buffer);
  fclose(file);
  printf("final content of variables\n");
  DisplayAllIDs();
  return 0;
}