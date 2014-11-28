#include <stdio.h>
#include <string.h>

struct case1
{
   char sign[4];
   char flag;
   long next[2];
}p[40001]={{'\0'},{'\0'},{0}};
char str[11]={'\0'};

int main()
{
   long i,j,n,m,k,t,p1=1,pk,s,flag=0;
   scanf("%ld%ld%ld\n",&n,&m,&k);
   k+=(!k);
   for (i=1;i<=n;i++)
      gets(p[i].sign);
   s=n;
   pk=((n<k)?n:k);
   pk+=(!pk);
   for (i=1;i<n;i++)
   {
      p[i].next[0]=i+1;
      p[i+1].next[1]=i;
   }
   for (i=1;i<=m;i++)
   {
      gets(str);
      if (str[0]=='A')
      {
         p[++s].next[flag]=p1;
         for (t=0;str[t+4]!=')';t++)
            p[s].sign[t]=str[t+4];
         p[p1].next[!flag]=s;
         p1=s;
         if (s>k)
         {
            p[pk].flag=flag;
            pk=p[pk].next[!flag];
         }
      }
      else
      {
         flag^=1;
         p[p1].next[flag]=p[pk].next[!flag];
         t=p1;
         p1=pk;
         pk=t;
      }
   }
   j=p1;
   for (i=1;i<=s;i++)
   {
      puts(p[j].sign);
      if (i<=k)
         j=p[j].next[flag];
      else
         j=p[j].next[p[j].flag];
   }
   return 0;
}
