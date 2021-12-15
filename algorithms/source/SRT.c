#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../FileManager.h"
#include "../../process.h"
//a function that swaps between 2 processes
void swap(Process *A,Process *B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}
int main(int argc, char* argv[]){
  FILE *file;
  int i=0,j,n,*tat,c,e=0,start=0, token;
  Process *p = NULL;
  int *gantt = NULL;
  char line[256];
  //checking if the config file exists or not
  if ((file = fopen(argv[1],"r")) == NULL){
      printf("Error! opening file");
      exit(1);
  }
  //get the total number of processes
  n =  getProcessnbFromFile(argv[1]);
  //save the name of the process i the first column and the start in the next 
  //gantt[n][2] 2 column to save name + starting start, n number of process
  gantt = (int *)malloc(n * 2 * sizeof(int));
  //allocating memory for the tables used
  p = (Process *)malloc(sizeof(Process) * n);
  tat = (int *)malloc(sizeof(int) * n);
  //print all information about the different processes
  printf("\tWelcome to Shortest Remaing Time Scheduling Algorithm\n");
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
      p[i].rnt=p[i].t_exec;
      printf("\t| %s  |       %d        |        %d       |     %d    |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      i++;
    }
  }
    puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  while (1){
    for (i=1;i<n;i++){
      /* swap when the remaining time of the current process is smaller then the remaining time of the 
      first process or when the first process is already executed*/
      if ((p[0].rnt==0 || start<p[0].t_arv?1:p[i].rnt<p[0].rnt || (p[i].rnt==p[0].rnt && p[i].t_arv<p[0].t_arv)) && start>=p[i].t_arv && p[i].rnt!=0)
      {
        swap(&p[0],&p[i]);
      }
    }
    /*extract the number of the current process */   
    token = atoi(strtok(p[0].pid,"P"));
    if (p[0].rnt!=0){
      //save the name and the starting time of the process
      if (e==0 || gantt[((e-1)*2) + 0]!=token){
        //name
        gantt[e*2 + 0]=token;
        //time
        gantt[((e++)*2) +1]=start;
      }
      /*check if the process finished the execution
      if he did the remaining time rnt should be 
      equal to 0 */
      if (--p[0].rnt==0){
        tat[0]=start+1;
      }
    }
    //start is the time when the next process will be executed
    start++;
    //counter variable used to check if there is still a process waiting for execution
    c=0;
    //check if there are other processes that are not executed
    for (i=0;i<n;i++){
      if (p[i].rnt!=0){
        c=1;
      }
    }
    // end of execution if no processes are left
    if (c==0)break;
  }
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