#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 17000
#define eps 1e-2
#define oo 1000000000
#define pi 3.14159265358979324
#define dis(x1,y1,z1,x2,y2,z2) (((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1))+((z2)-(z1))*((z2)-(z1)))

struct case1
{
   double x,y,z;
}p[N+1]={0,0,0};
long d[40000]={0},head[N+1]={0},e[60*N+1]={0},next[60*N+1]={0};
double v[60*N+1]={0},dis[N+1]={0};
char hash[N+1]={0};
long totm=0;

void add(long a,long b,double c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
   v[totm]=c;
}

int main()
{
   long i,j,now,st=1,en=1;
   double r,tmp;
   srand((unsigned)time(NULL));
   scanf("%lf%lf%lf%lf%lf%lf",&p[1].x,&p[1].y,&p[1].z,&p[2].x,&p[2].y,&p[2].z);
   if (dis(p[1].x,p[1].y,p[1].z,p[2].x,p[2].y,p[2].z)<=eps)
      add(1,2,sqrt(dis(p[1].x,p[1].y,p[1].z,p[2].x,p[2].y,p[2].z)));
   for (i=3;i<=N;i++)
   {
      p[i].z=2.0*rand()/32767-1;
      r=sqrt(1+p[i].z*p[i].z);
      tmp=2*pi*rand()/32768;
      p[i].x=r*cos(tmp);
      p[i].y=r*sin(tmp);
      for (j=1;j<i;j++)
         if ((tmp=dis(p[i].x,p[i].y,p[i].z,p[j].x,p[j].y,p[j].z))<=eps)
            add(i,j,sqrt(tmp));
   }
   d[1]=1;
   for (i=2;i<=N;i++)
      dis[i]=oo;
   while (st<=en)
   {
      now=d[(st++)&32767];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (dis[now]+v[i]<dis[e[i]])
         {
            dis[e[i]]=dis[now]+v[i];
            if (!hash[e[i]])
            {
               hash[e[i]]=1;
               d[(++en)&32767]=e[i];
            }
         }
   }
   printf("%lf\n",dis[2]);
   return 0;
}
