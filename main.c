#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "process.h"
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
int main(int argc, char* argv[]){
    FILE *file;    
    struct dirent *pDirent;
    DIR *pDir;
    int nbAlgo=1,n;
    char choix[256][256];
    char path[256];
    //checking if the config file exists or not
    if ((file = fopen(argv[1],"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //get all the algorithms present in the "algorithms" directory
    pDir = opendir ("./algorithms/build/");
    if (pDir == NULL) 
        printf ("Cannot open directory");
    else{
        printf("\t\t\t     Algorithm Game\n");
        puts("\t\t\t¤ ~~~ ¤ ¤ ~~~ ¤ ¤ ~~~ ¤");
        while ((pDirent = readdir(pDir)) != NULL ) {
            if (strlen(pDirent->d_name)>1 && strstr(pDirent->d_name, "..")== NULL && strstr(pDirent->d_name, ".o")== NULL) {
                strcpy(choix[nbAlgo],pDirent->d_name);
                printf ("\t\t\t\t%d. %s\n",nbAlgo,choix[nbAlgo]);
                nbAlgo++;
            }

        }
        printf("\t\t\t\t%d. Exit\n", nbAlgo);
        puts("\t\t\t¤ ~~~ ¤ ¤ ~~~ ¤ ¤ ~~~ ¤");        closedir (pDir);
    }
    //menu display
    printf("%s\n",path);
    while(1) {
        printf("Enter your choice :  \n");
        scanf("%d",&n);
        strcpy(path,"./algorithms/build/");
        strcat(path, choix[n]);
        strcat(path, " ");
        strcat(path, argv[1]);
        if ( n<=nbAlgo-1) {
            system(path);
            printf("\n\n");

        } else {
            if( n == nbAlgo) {
            exit(0);    // terminates the complete program execution
            }else {
                printf("Please choose an option by entering the corresponding number\n ");
            }

        }
    }
    fclose(file);
}