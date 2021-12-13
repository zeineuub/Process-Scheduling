#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../process.h"
//a function that swaps between 2 processes
void swap(Process *A,Process *B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}
int main(int argc, char* argv[]){	
  FILE *file;
  int i=0,j,n,k,t,e=0,m=0,token, start;
  Process *p = NULL;
  //checking if the config file exists or not
  if ((file = fopen(argv[1],"r")) == NULL){
      printf("Error! opening file");
      exit(1);
  }
  fscanf(file, " %d", &n);
  //save the name of the process i the first column and the time in the next 
  //gantt[n][2] 2 column to save name + starting time, n number of process
  int gantt[n][2];
  p = (Process *)malloc(sizeof(Process) * n);
  //display the list of process
  printf("\t  Welcome to Shortest Job First Scheduling Algorithm\n");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  puts("\t| PID |  Arrival Time  |   Burst Time   | Priority |");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  while (i < n){
      fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
      printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      i++;
  }
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  //Sorting the processes according to their arrival time and burst time
  for(i=0;i<n;i++){
    for(j=i+1;j<n;j++){
      if((p[i].t_arv> p[j].t_arv) || ((p[i].t_arv==p[j].t_arv) && (p[i].t_exec>p[j].t_exec))){
        /*swap when the process have the smallest arrival time and 
        if the 2 processes are equal take the one with the smallest burst time*/
        swap(&p[i], &p[j]); 
      }
    }
  }
  k = p[0].t_arv + p[0].t_exec;
  for(i=1;i<n;i++){
    for(j=i+1;j<n;j++){
      /*swap when the burst time of process i is greater then process j at k time */
      if(p[i].t_exec>p[j].t_exec && k>=p[j].t_arv){
        m=1;
        swap(&p[i], &p[j]); 
      }
    }
    if (m==0){
      k=k+p[i].t_exec;
    }else{
      k++;
    }
    m=0;
  }
  start=0;
  for(i=0;i<n;i++){
    /*extract the number of the current process */    
    token = atoi(strtok(p[i].pid,"P"));
    if (start-p[i].t_arv<0){
      gantt[e][0]=-1;
      gantt[e++][1]=start;
      start+=p[i].t_arv-start;
    }
    gantt[e][0]=token;
    //save the name of the process that will be executed
    gantt[e++][1]=start;
    //the process i+1 will start after the process i completes it's execution
    start+=p[i].t_exec;    
  }
  gantt[e][1]=start;
  printf("\n\nThe Gantt chart is:\n\n");
  printf (" ");
  for (i=0;i<e;i++){
    printf ("---- ");
  }
  printf ("\n");
  //display the name of processes
  for (i=0;i<e;i++){   
    printf (gantt[i][0]==-1?"|   ":"| P%d ",gantt[i][0]);
  }
  printf ("|\n ");
  for (i=0;i<e;i++){
    printf ("---- ");
  }
  //display the (start,end) time of each process
  printf ("\n");
  for (i=0;i<=e;i++){   
    printf ("%d    ",gantt[i][1]);
  }
  return 0;
}