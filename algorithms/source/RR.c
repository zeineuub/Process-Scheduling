#include<stdio.h>
#include <stdlib.h>
#include "../../process.h"
#include "../../FileManager.h"
int main(int argc, char* argv[]){
    int i=0, j=0, n, len=0, count=0, front=0, rear=-1, e=0;
    FILE *file;
    char line[256];
    Process *p = NULL;
    quantum ts;
    int *ready= NULL;
    int *gantt = NULL;
    //checking if the configuration file exists or not
    if ((file = fopen(argv[1],"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //get the total number of processes
    n =  getProcessnbFromFile(argv[1]);

    //allocating memory for the tables used
    p = (Process *)malloc(sizeof(Process) * n);
    
    //print all information about the different processes
    printf("\t     Welcome to Round Robin Scheduling Algorithm\n");
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
            //initialization of the remaining burst time and for the remaining burst time table
            p[i].rnt=p[i].t_exec;
            //get the total excution time for all the processes
            len+=p[i].t_exec;
            printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
            i++;
        }
    }
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    fclose(file);
    //save the name of the process i the first column and the time in the next 
    //gantt[n][2] 2 column to save name + starting time, n number of process
    gantt = (int *)malloc(n * 2 * sizeof(int));
    // allocation of the ready que
    ready= (int *)malloc(sizeof(int) * len);
    
    //get the quantum value from the user
    while(ts==0 ){
        printf("Enter Time Slice OR Quantum Number : ");
        scanf("%d",&ts);
    }
    //looping until all processes complete their execution time
    while(j<n){
        int found=0;
        if(front>rear){
            for(i=0;i<n;i++){
                /*if the current process's arrival time is equal to the ongoing excution time
                then make the current process ready for excution*/
                if(p[i].t_arv==count){
                    ready[++rear]=i;
                    found=1;
                }
            }              
        }
        else{
            int k,ind=ready[front++];
            //saving the indice of the process
            gantt[e*2 +0]=ind+1;
            //saving the starting time
            gantt[((e++)*2) +1]=count;
            /*if the process's remaining burstime is less then the chosen quantum
            then we complete it's execution and then we move on to the next process*/
            if(p[ind].rnt<=ts){
                //looping through the remaining burst time
                for(k=0;k<p[ind].rnt;k++){
                    count++;
                    //getting the next process ready and advancing the execution variable
                    for(i=0;i<n;i++){
                        //checking if there' a new process to add to the stack based on the arrival time
                        if(p[i].t_arv==count)ready[++rear]=i;
                    }
                }
                p[ind].rnt<=0;
                j++;
            }
            /*if the process's remaining burst time is greater then
            we only excute the quantum's length of the remaining time and then we move on to the next process*/
            else{
                for(k=0;k<ts;k++){
                    count++;
                    //looping through the remaining burst time and excuting only the quantum's length
                    for(i=0;i<n;i++){
                        if(p[i].t_arv==count)ready[++rear]=i;
                    }
                }
                //substracting the quantum's length from the process's remaing time and getting the next process ready
                p[ind].rnt-=ts;
                ready[++rear]=ind;
            }
        }
    }
    //displaying the gant chart
    gantt[e*2 +1]=count;
    
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