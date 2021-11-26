#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../../process.h"
void sortart(Process *p,int n)
{
  int i,j;
  Process *temp;
  for(i=0;i<n;i++){
    for(j=i+1;j<n;j++){
      if(p[i].priorite > p[j].priorite){
        temp = p[i].priorite ;
        p[i].priorite = p[j].priorite;
        p[j].priorite = temp;
      }
    }
  }
  return;
}
int main(int argc, char* argv[]){

  FILE *file;
  int i=0,j,n,gantt[100][2],c,d,e=0,f=0,g,time=0,tat[20],token;
  char choix[256][256];
  Process *p = NULL;
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
      p[i].rnt=p[i].t_exec;
      printf("%d",p[i].priorite);
      printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
      i++;
  }
  while (1){
    sortart(p,n);
    token = atoi(strtok(p[0].pid, "P"));
    if (p[0].rnt!=0){
      if (f==0 || gantt[f-1][0]!=token)
      {
        gantt[f][0]=token;
        gantt[f++][1]=time;
      }
      if (--p[0].rnt==0){
        tat[0]=time+1-p[0].t_arv;
      }
    }
  time++;
  printf("%d",time);
  c=0;
  for (i=0;i<e;i++){
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