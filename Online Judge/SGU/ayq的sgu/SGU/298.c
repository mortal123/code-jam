#include <stdio.h>
#define oo 1000000000

long head[10002]={0},next[120001]={0},e[120001]={0},v[120001]={0},time[10002]={0},dis[10002]={0},d[32769]={0};
char hash[10002]={'\0'};
long totm=0;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

int main()
{
   long i,a,b,c,n,m,now,st=3276801,en=3276801;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld",&a,&b,&c);
      add(b,a,c);
   }
   for (i=1;i<=n;i++)
   {
      add(i,n+1,-10000);
      add(n+1,i,-10000);
      dis[i+1]=-oo;
   }
   d[1]=1;
   m+=2*n;
   n++;
   while (st<=en)
   {
      now=d[(st++)&32767];
      hash[now]=0;
      for (i=head[now];i;i=next[i])
         if (dis[e[i]]<dis[now]+v[i])
         {
            dis[e[i]]=dis[now]+v[i];
            if (!hash[e[i]])
            {
               hash[e[i]]=1;
               if (dis[e[i]]>dis[d[st&32767]])
                  d[(--st)&32767]=e[i];
               else
                  d[(++en)&32767]=e[i];
               time[e[i]]++;
               if (time[e[i]]>n||en>3276801+2*m)
                  goto out;
            }
         }
   }
   out:
   if (st<=en)
      printf("-1\n");
   else
      for (i=1;i<n;i++)
         printf("%ld%c",dis[i]-dis[n],(i==(n-1))?'\n':' ');
   return 0;
}
