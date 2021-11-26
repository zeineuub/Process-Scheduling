#include<stdio.h>
#include <stdlib.h>
#include "../../process.h"
void sortart(Process *p,int n)
{
       int i,j;
       Process *temp;
       for(i=0;i<n;i++)
       {
              for(j=i+1;j<n;j++)
              {
                     if(p[i].t_arv > p[j].t_arv)
                     {
                           temp = p[i].t_arv ;
                           p[i].t_arv  = p[j].t_arv ;
                           p[j].t_arv = temp;
                     }
              }
       }
       return;
}
int main(int argc, char* argv[])
{
int i,j,n,time,remain,flag=0, *wtt, *tat;
float avgwt=0,avgtt=0;
FILE *file;
Process *p = NULL;
quantum ts;
char choix[256][256];
if ((file = fopen(argv[1],"r")) == NULL){
    printf("Error! opening file");
    exit(1);
}
fscanf(file, " %d", &n);
p = (Process *)malloc(sizeof(Process) * n);
tat = (int *)malloc(sizeof(int) * n);
wtt = (int *)malloc(sizeof(int) * n);

puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
while (i < n){
    fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
    p[i].rnt=p[i].t_exec;
    printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
    i++;
}
       remain=n;
       sortart(p,n);
       printf("Enter Time Slice OR Quantum Number : ");
       scanf("%d",&ts);
       printf("\n***************************************\n");
       printf("Gantt Chart\n");
       for(time=0,i=0;remain!=0;)
       {
              if(p[i].rnt<=ts && p[i].rnt>0)
              {
                     time = time + p[i].rnt;

                     printf(" -> [%s] <- %d",p[i].pid,time);
                     p[i].rnt=0;
                     flag=1;
              }
              else if(p[i].rnt > 0)
              {
                     p[i].rnt = p[i].rnt - ts;
                     time = time + ts;
                     printf(" -> [%s] <- %d",p[i].pid,time);
              }
              if(p[i].rnt==0 && flag==1)
              {
                     remain--;
                     tat[i] = time-p[i].t_arv;
                     wtt[i] = time-p[i].t_arv-p[i].t_exec;
                     avgwt = avgwt + time-p[i].t_arv-p[i].t_exec;
                     avgtt = avgtt + time-p[i].t_arv;
                     flag=0;
              }
              if(i==n-1)
                     i=0;
              else if(p[i+1].t_arv<= time)
                     i++;
              else
                     i=0;
       }
       printf("\n\n");
       printf("***************************************\n");
       return 0;
}