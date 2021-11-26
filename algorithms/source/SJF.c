#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../process.h"
int gantt[20][2],t1;
void swap(Process *A,Process *B){
    Process temp = *A;
    *A = *B;
    *B = temp;
}
int main(int argc, char* argv[])
{	
FILE *file;
int i,j,n,k,t,e=0,m=0,*w,token;
float aw,at,sum1; 
Process *p = NULL;
char choix[256][256];
if ((file = fopen(argv[1],"r")) == NULL){
    printf("Error! opening file");
    exit(1);
}
fscanf(file, " %d", &n);
p = (Process *)malloc(sizeof(Process) * n);
w = (int *)malloc(sizeof(int) * n);

puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
puts("\t| PID | Temps d'arrivé | Temps d'execution | Priorite |");
puts("\t¤ ~~~ ¤ ~~~~~~~~~~~~~~ ¤ ~~~~~~~~~~~~~~~~~ ¤ ~~~~~~~~ ¤");
while (i < n){
    fscanf(file, "%s %d %d %d",p[i].pid,&p[i].t_arv,&p[i].t_exec,&p[i].priorite);
    printf("\t| %s  |       %d        |          %d        |    %d     |\n",p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
    i++;
}
for(i=0;i<n;i++)
{
    for(j=i+1;j<n;j++)
    {
       if((p[i].t_arv> p[j].t_arv) || ((p[i].t_arv==p[j].t_arv) && (p[i].t_exec>p[j].t_exec)))
        {
            swap(&p[i], &p[j]); 
        }
    }
}
k = p[0].t_arv + p[0].t_exec;
for(i=1;i<n;i++)
{
    for(j=i+1;j<n;j++)
    {
      if(p[i].t_exec>p[j].t_exec && k>=p[j].t_arv)
        {
        m=1;
        swap(&p[i], &p[j]); 
        }
    }
    if (m==0)
    {
        k=k+p[i].t_exec;
    }
    else{
       k++;
    }
    m=0;

}
t1=0;
for(i=0;i<n;i++)
{
  token = atoi(strtok(p[i].pid,"P"));
  if (t1-p[i].t_arv<0)
    {
     gantt[e][0]=-1;
     gantt[e++][1]=t1;
     t1+=p[i].t_arv-t1;
    }
   if(i==0)
    {
        w[i]=0;
    }
   else{    
      w[i]=t1-p[i].t_arv;
    }
    gantt[e][0]=token;
    gantt[e++][1]=t1;
    t1+=p[i].t_exec;
    
}
gantt[e][1]=t1;
printf("\n\nThe Gantt chart is:\n\n");
 /*for(i=0;i<n;i++)
  {
   printf("|%d",p[i]);
    if(i==n-1)
     printf("|");
  } */
  printf (" ");
  for (i=0;i<e;i++)
   {printf ("---- ");}
  printf ("\n");
  for (i=0;i<e;i++)
  {   
    printf (gantt[i][0]==-1?"|   ":"| P%d ",gantt[i][0]);
  }
  printf ("|\n ");
  for (i=0;i<e;i++)
  {
   {printf ("---- ");}
  }
  printf ("\n");
  for (i=0;i<=e;i++)
  {   
    printf ("%d    ",gantt[i][1]);
  }
return 0;
}