#include <stdio.h>

long num[2000001]={0};

int main()
{
   long i,n,m,q,t,x,flag=1,now=1;
   scanf("%d%d",&n,&q);
   m=(q?n/10:n)+1;
   for (i=1;i<=n;i++)
      num[i]=i;
   x=n;
   while ((x--)>1)
   {
      for (i=1;i<q;i++)
         if (flag)
            do
               now=((now==n)?1:now+1);
            while (!num[now]);
         else
            do
               now=((now==1)?n:now-1);
            while (!num[now]);
      num[now]=0;
      while (!num[now])
         now=((now==n)?1:now+1);
      flag=(num[now]&1);
      if (!(x%m))
      {
         t=0;
         for (i=1;i<=n;i++)
            if (num[i])
            {
               num[++t]=num[i];
               if (i==now)
                  now=t;
            }
         n=t;
      }
   }
   printf("%ld\n",num[now]);
   return 0;
}
