#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../process.h"
#include "../../FileManager.h"
//a function that swaps between 2 processes
void swap(Process *A,Process *B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}
int main(int argc, char* argv[]){	
    FILE *file;
    int i=0,j,n,e=0,token,start=0;
    Process *p = NULL;
    int *gantt = NULL;
    char line[256];

    //checking if the configuration file exists or not
    if ((file = fopen(argv[1],"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //get the total number of processes
    n =  getProcessnbFromFile(argv[1]);
    //allocating memory for the table used
    p = (Process *)malloc(sizeof(Process) * n);
    //print all information about the different processes
    printf("\t Welcome to First In First Out Scheduling Algorithm\n");
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
            printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
            i++;
        }
    }
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    fclose(file);
    //save the name of the process i the first column and the time in the next 
    //gantt[n][2] 2 column to save name + starting time, n number of process
    gantt = (int *)malloc(n * 2 * sizeof(int));
    //Sorting the processes according to their arrival time
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(p[i].t_arv> p[j].t_arv){
                swap(&p[i], &p[j]); 
            }
        }
    }
    for(i=0;i<n;i++){
        //get the current process's number
        token = atoi(strtok(p[i].pid,"P"));
        //save the name of the process that will be executed
        gantt[e*2 +0]=token;
        //save the starting time of the current process 
        gantt[((e++)*2) +1]=start;
        //the process i+1 will start after burst time of the process i
        start+=p[i].t_exec;
    }
    //displaying the gant chart
    gantt[e*2 +1]=start;
    printf("\n\nThe Gantt chart is:\n");
    printf(" ");
    for (i=0;i<e;i++){
        printf (" ¤---¤  ");
    }
    printf ("\n");
    //display the name of each process
    for (i=0;i<e;i++){   
        printf ("|  P%d\t",gantt[i*2 + 0]);
    }
    printf ("|\n ");
    for (i=0;i<e;i++){
        printf (" ¤---¤  ");
    }
    printf ("\n");
    //display the (start,end) time of each process
    for (i=0;i<=e;i++){   
        printf ("%d\t",gantt[i*2 + 1]);
    }
    return 0;
}