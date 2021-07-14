/*This 2 function are used to display a significant error message 
To indicate the location of the error using the famous token
*/

//Display a char in this way @a to say adress 
/*static
char IsPrintChar(char c) {
  if (  isprint(c)  )//ex '\t' can not be printed
    return c;
  return '@';
}*/
// A printable version of string that contains more then 100 chars
/*static
char *IsPrintString(char *s) {
  static char tab[101];
  int i;
  int n = strlen(s);
  if (  n > 100  )
    n = 100;
  for (i=0; i<n; i++)
    tab[i] = IsPrintChar(s[i]);
  tab[i] = 0;
  return tab;
}*/