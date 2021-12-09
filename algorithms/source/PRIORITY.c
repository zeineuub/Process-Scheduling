#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../../process.h"
int main(int argc, char* argv[]){

  FILE *file;
  int i=0,j=0,n,*Rt,*Ct,count=0,prev=-1,dec=0,choice,ind=-1;
  Process *p = NULL;
  //checking if the config file exists or not
  if ((file = fopen(argv[1],"r")) == NULL){
      printf("Error! opening file");
      exit(1);
  }
  //get the total number of processes
  fscanf(file, " %d", &n);
  //allocating memory for the tables used
  p = (Process *)malloc(sizeof(Process) * n);
  Rt = (int *)malloc(sizeof(int) * n);
  Ct = (int *)malloc(sizeof(int) * n);
  //print all information about the different processes
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  while (i < n){
      fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
      //initialization of the remiaing burst time and for the remaining burst time table
      p[i].rnt=p[i].t_exec;
      Rt[i]=-1;
      printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      i++;
  }
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  //displaying the gant chart
  printf("\nGantt chart:\n|");
  
  
  while(j<n)
  {
    int min=0,ind=-1;
    for(i=0;i<n;i++){
      /*checking if the current process's priority is the stored one 
      while making sure that it still got burst time left*/
      if(p[i].priorite==min && p[i].rnt>0){
        /*checking if the current process's arrival time exceds the indexed one's 
          if so the current process becomes the indexed one*/
        if(p[i].t_arv>p[ind].t_arv)ind=i;
      }
      /*checking if the current process's priority is bigger then the currently stored priority value
       while checking if the process still has burst time left*/
      else if(p[i].priorite>min && p[i].rnt>0){
        //checking if the process's arrival time is less then the current excution time
        if(p[i].t_arv<=count){
          //storing the current process's priority and storing it's index
          min=p[i].priorite;
          ind=i;
        }
      }
    }
    //checking if we have a process's index already stored
    if(ind!=-1){
      //the currently indexed process was executed
      p[ind].rnt-=1;
      //checking if the currently indexed process is not the previous one executed
      if(ind!=prev)printf("%d-P%d-",count,(ind+1));
    }else{
      //calculating the remaining burst time after the execution
      dec=1;
      }
      if(ind!=prev && Rt[ind]==-1)Rt[ind]=count-p[ind].t_arv;     
      count++;
      //if the indexed process has finished all of it's burst time we move to the next one
      if(p[ind].rnt==0 && ind!=-1){
        Ct[ind]=count;
        j++;
        dec=0;
      }
      //the previously executed process becomes the current one
      prev=ind;
    }
    //printing the final execution time
  printf("%d|\n",count);
  return 0;
}


