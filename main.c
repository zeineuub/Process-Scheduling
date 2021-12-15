#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "process.h"
#include "FileManager.h"
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
    char line[256];
    int nbAlgo=1,n,i=0,nb=0;
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
            if (strlen(pDirent->d_name)>1 && strstr(pDirent->d_name, "..")== NULL) {
                strcpy(choix[nbAlgo],pDirent->d_name);
                printf ("\t\t\t\t%d. %s\n",nbAlgo,choix[nbAlgo]);
                nbAlgo++;
            }

        }
        printf("\t\t\t\t%d. Exit\n", nbAlgo);
        puts("\t\t\t¤ ~~~ ¤ ¤ ~~~ ¤ ¤ ~~~ ¤");        closedir (pDir);
    }
      Process *p = NULL;
  //checking if the configuration file exists or not
  if ((file = fopen(argv[1],"r")) == NULL){
      printf("Error! opening file");
      exit(1);
  }
  //get the total number of processes
  nb =  getProcessnbFromFile(argv[1]);
  //allocating memory for the tables used
  p = (Process *)malloc(sizeof(Process) * nb);
  //print all information about the different processes
  printf("\t         Welcome to Scheduling Algorithm\n");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  puts("\t| PID |  Arrival Time  |   Burst Time   | Priority |");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  while (fgets(line, sizeof(line), file)){
    //first character of the line
    char firstChar = line[0];
    // check if line is empty or is a comment
    if ((firstChar != '#') && (strlen(line) > 2)){
      //separator
      char d[] = " ";
      //Save process details in "p"
      strcpy(p[i].pid, strtok(line, d));
      p[i].t_arv = atoi(strtok(NULL, d));
      p[i].t_exec = atoi(strtok(NULL, d));
      p[i].priorite = atoi(strtok(NULL, d));
      //initialization of the remiaing burst time and for the remaining burst time table
      p[i].rnt=p[i].t_exec;
      printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      i++;
    }
  }
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
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