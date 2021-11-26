#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80
int main()
{
int num;
FILE *file;
int i=0;
char line[4] = {0};
char ch;
unsigned int line_count = 0;
int n=0;
   if ((file = fopen("FileConf.txt","r")) == NULL){
       printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
       exit(1);
   }
    /* Get each line until there are none left */
while((ch = fgetc(file)) != EOF)
      printf("%c\n", ch);
        i++;
fclose(file);

return 0;
}
