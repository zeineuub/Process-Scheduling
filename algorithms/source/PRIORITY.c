#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../../FileManager.h"
#include "../../process.h"
int main(int argc, char* argv[]){

  FILE *file;
  char line[256];
  int i=0,j=0,n,count=0,prev=-1,choice,ind=-1;
  Process *p = NULL;
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
  printf("\t     Welcome to Priority Scheduling Algorithm\n");
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
  //displaying the gant chart
  printf("\nGantt chart:\n|");
  
  
  while(j<n)
  {
    int max=0,ind=-1;
    for(i=0;i<n;i++){
      /*checking if the current process's priority is the stored one 
      while making sure that it still got burst time left*/
      if(p[i].priorite==max && p[i].rnt>0){
        /*checking if the current process's arrival time exceds the indexed one's 
          if so the current process becomes the indexed one*/
        if(p[i].t_arv>p[ind].t_arv)ind=i;
      }
      /*checking if the current process's priority is bigger then the currently stored priority value
       while checking if the process still has burst time left*/
      else if(p[i].priorite>max && p[i].rnt>0){
        //checking if the process's arrival time is less then the current excution time
        if(p[i].t_arv<=count){
          //storing the current process's priority and storing it's index
          max=p[i].priorite;
          ind=i;
        }
      }
    }
    //checking if we have a process's index already stored
    if(ind!=-1){
      //updating the remaining execution time
      p[ind].rnt-=1;
      /*checking if the currently indexed process
       is not the previous one executed*/
      if(ind!=prev)printf("%d-P%d-",count,(ind+1));
    }
    //update the next starting time for the nex process     
    count++;
    //if the indexed process has finished all of it's burst time we move to the next one
    if(p[ind].rnt==0 && ind!=-1){
      //move one to teh next process
      j++;
    }
    //the previously executed process becomes the current one
    prev=ind;
    }
    //printing the final execution time
  printf("%d|\n",count);
  return 0;
}


