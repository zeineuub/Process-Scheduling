#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../process.h"
void swap(Process *A,Process *B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}
int main(int argc, char* argv[])
{
  FILE *file;
  int i,j,n,tat[20],gantt[100][2],c,f=0,g,time=0, token;
  Process *p = NULL;
  char choix[256][256];
  if ((file = fopen(argv[1],"r")) == NULL){
      printf("Error! opening file");
      exit(1);
  }
  fscanf(file, " %d", &n);
  p = (Process *)malloc(sizeof(Process) * n);
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
  puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
  while (i < n){
      fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
      printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      p[i].rnt=p[i].t_exec;
      i++;
  }
  while (1){
    for (i=1;i<n;i++){
      if ((p[0].rnt==0 || time<p[0].t_arv?1:p[i].rnt<p[0].rnt || (p[i].rnt==p[0].rnt && p[i].t_arv<p[0].t_arv)) && time>=p[i].t_arv && p[i].rnt!=0)
      {
        swap(&p[0],&p[i]);
      }
    }
    token = atoi(strtok(p[0].pid,"P"));
      if (p[0].rnt!=0){
        if (f==0 || gantt[f-1][0]!=token){
          gantt[f][0]=token;
          gantt[f++][1]=time;
        }
        if (--p[0].rnt==0){
        tat[0]=time+1;
        }
      }
    time++;
    c=0;
    for (i=0;i<n;i++){
      if (p[i].rnt!=0){
        c=1;
      }
    }
    if (c==0)break;
  }
  gantt[f][1]=time;
  printf("\n\nThe Gantt chart is:\n\n");
  printf (" ");
  for (i=0;i<f;i++){
    printf ("---- ");
  }
  printf ("\n");
  for (i=0;i<f;i++){ 
    printf (gantt[i][0]==-1?"|   ":"| P%d ",gantt[i][0]);
  } 
  printf ("|\n ");
  for (i=0;i<f;i++){
    printf ("---- ");
  }
  printf ("\n");
  for (i=0;i<=f;i++){
    printf ("%d    ",gantt[i][1]);
  }

  return 0;
} 