#include<stdio.h>
#include <stdlib.h>
#include "../../process.h"
int main(int argc, char* argv[]){
    int i=0,j,n, len=0, *rt, *ct;
    FILE *file;
    Process *p = NULL;
    quantum ts;
    //checking if the config file exists or not
    if ((file = fopen(argv[1],"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
    //get the total number of processes
    fscanf(file, " %d", &n);
    //allocating memory for the tables used
    p = (Process *)malloc(sizeof(Process) * n);
    rt = (int *)malloc(sizeof(int) * n);
    ct = (int *)malloc(sizeof(int) * n);
    //print all information about the different processes
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    while (i < n){
        fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
        //initialization of the remaining burst time and for the remaining burst time table
        p[i].rnt=p[i].t_exec;
        rt[i]=-1;
        //get the total excution time
        len+=p[i].t_exec;
        printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
        i++;
    }
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
    //get the quantum value from the user
    printf("Enter Time Slice OR Quantum Number : ");
    scanf("%d",&ts);
    int ready[len];
    int count=0,front=0,rear=-1,dec=0;
    j=0;
    //displaying the gant chart
    printf("\nGantt chart:\n|");
    //looping until all processes complete their execution time
    while(j<n){
        int found=0;
        if(front>rear){
            for(i=0;i<n;i++)
                /*if the current process's arrival time is equal to the ongoing excution time
                then make the current process ready for excution*/
                if(p[i].t_arv==count){
                    ready[++rear]=i;
                    found=1;
                }
            }
        else{
            int k,ind=ready[front++],dec=0;
            //print the process excution
            printf("%d-P%d-",count,(ind+1));
            /*if the indexed process's remaining burst time is the default value
            then it gets assigned to the remaining burst time from the previous execution*/
            if(rt[ind]==-1)
            rt[ind]=count-p[ind].t_arv;
            /*if the process's remaining burstime is less then the chosen quantum
            then we complete it's execution and then we move on to the next process*/
            if(p[ind].rnt<=ts){
                //looping through the remaining burst time
                for(k=0;k<p[ind].rnt;k++){
                    count++;
                    //getting the next process ready and advancing the execution variable
                    for(i=0;i<n;i++){
                        if(p[i].t_arv==count)ready[++rear]=i;
                    }
                }
                p[ind].rnt<=0;
                ct[ind]=count;
                j++;
            }
            /*if the process's remaining burstime is greater then
            the chosen quantum then we only excute the quantum's length of the remaining time and then we move on to the next process*/
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
    //printing the final execution time
    printf("%d|\n",count);
    return 0;
}