#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define MAX_LINE_LENGTH 80
#include "process.h"
char menuDisplay(FILE *file) {
    struct dirent *pDirent;
    DIR *pDir;
    int nbAlgo=0;
    char choix[256][256];
    pDir = opendir ("./algorithms/build/");
    if (pDir == NULL) 
        printf ("Cannot open directory");
    else{
        while ((pDirent = readdir(pDir)) != NULL ) {
            if(strcmp(strcat(pDirent->d_name[strlen(pDirent->d_name)-2],pDirent->d_name[strlen(pDirent->d_name)-1]), ".o"))continue;
            if (strlen(pDirent->d_name)>2 && strcmp(pDirent->d_name, "algorithms.h") !=0) {
                pDirent->d_name[strlen(pDirent->d_name)-2] = '\0';
                strcpy(choix[nbAlgo],pDirent->d_name);
                printf ("%s\n", choix[nbAlgo]);
                nbAlgo++;
            }

        }
        closedir (pDir);
    }
    return choix;
}
Process *processTable(FILE *file) {
    int i=0;
    int n=0;
    Process *p = NULL;
    fscanf(file, " %d", &n);
    p = (Process *)malloc(sizeof(Process) * n);
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    while (i < n){
        fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
        printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
    
        i++;
    }
    rewind(file);
}
int main(int argc, char* argv[])
{
FILE *file;
char choix[256][256];
if ((file = fopen(argv[1],"r")) == NULL){
    printf("Error! opening file");
    exit(1);
}
menuDisplay(file);
processTable(file);
fclose(file);
}