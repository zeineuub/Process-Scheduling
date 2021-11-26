#include<stdio.h>
#include <stdlib.h>
#include "../../process.h"

int main(int argc, char* argv[])
{	
FILE *file;
int n=0,i,j,start,pos,max=0,min,idle=0,k=0;
float av1=0,av2=0;
int *at2,*ex, *seq, *re, *wt, *tat;
Process *p = NULL;
char choix[256][256];
if ((file = fopen(argv[1],"r")) == NULL){
    printf("Error! opening file");
    exit(1);
}
fscanf(file, " %d", &n);
seq = (int *)malloc(sizeof(int) * n);
p = (Process *)malloc(sizeof(Process) * n);
puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
while (fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite)!=EOF){
    printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
    i++;
}
// first process P1
start=p[0].t_arv;
// search which process gonna start first
for(i=1;i<n;i++)
{
    if(start>p[i].t_arv)
    {
        start=p[i].t_arv;
    }
}
printf("*****OUTPUT*****\n");
printf("Sequence of execution is\n");
for(i=0;i<n;i++)
{
    if(max<p[i].t_arv)
    {
        max=p[i].t_arv;
    }
}
max=max+1;
for(i=0;i<n;i++,k++)
{  
       min=max;
       for(j=0;j<n;j++)
       {  
           if(p[j].t_arv!=-1)
            {
               if(p[j].t_arv<min)
                {
                  min=p[j].t_arv;
                  pos=j;
                }
            }
        }
      printf("[P%d]  ",pos);
      seq[k]=pos;
      if(start<p[pos].t_arv)
      {
        start=p[pos].t_arv;
        start+=p[pos].t_exec;
        p[pos].t_arv=-1;
      }
      else
      {
        start+=p[pos].t_exec;
        p[pos].t_arv=-1;
       }
     }
    return 0;
}