#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../process.h"
//calculate the number of occrence
int nbr_occ(char s[100]) {
    int occ = 0;
    int i;
    int len = strlen(s);
    for (i = 0; s[i] != '\0'; ++i){
        if (s[i] == ' '){
            ++occ;
        }
    }
    return occ;
}
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
    char line[256];
    //checking if the config file exists or not
    if ((file = fopen(argv[1],"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //display the list of process
    printf("\t Welcome to First In First Out Scheduling Algorithm\n");
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    puts("\t| PID |  Arrival Time  |   Burst Time   | Priority |");
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    fgets(line, sizeof(line), file);
    if (atoi(line) != 0){
        n = atoi(line);
        p = (Process *)malloc(sizeof(Process) * n);
        while ((i < n) && (fgets(line, sizeof(line), file))){
            if (nbr_occ(line) > 2){
                sscanf(line, "%s %d %d %d",p[i].pid, &p[i].t_arv, &p[i].t_exec, &p[i].priorite);
                printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
                i++;
            }
        }
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");

    }
    fclose(file);
    //save the name of the process i the first column and the time in the next 
    //gantt[n][2] 2 column to save name + starting time, n number of process
    int gantt[n][2];
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
        if (start-p[i].t_arv<0){
            gantt[e][0]=-1;
            gantt[e++][1]=start;
            start+=p[i].t_arv-start;
        }
        //save the name of the process that will be executed
        gantt[e][0]=token;
        //save the starting time of the current process 
        gantt[e++][1]=start;
        //the process i+1 will start after burst time of the process i
        start+=p[i].t_exec;
        
    }
    //displaying the gant chart
    gantt[e][1]=start;
    printf("\n\nThe Gantt chart is:\n\n");

    printf (" ");
    for (i=0;i<e;i++){
        printf ("---- ");
    }
    printf ("\n");
    //display the name of each process
    for (i=0;i<e;i++){   
        printf (gantt[i][0]==-1?"|   ":"| P%d ",gantt[i][0]);
    }
    printf ("|\n ");
    for (i=0;i<e;i++){
        printf ("---- ");
    }
    printf ("\n");
    //display the (start,end) time of each process
    for (i=0;i<=e;i++){   
        printf ("%d    ",gantt[i][1]);
    }
    return 0;
}