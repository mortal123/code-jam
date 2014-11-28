#include<stdio.h>

long hp[7]={0},score[7]={0};

int main()
{
   long i,n,m,a,b;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      hp[i]=100;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      if (hp[a]>0)
      {
         if (hp[b]>0)
            score[a]+=3;
         hp[b]-=8;
      }
   }
   for (i=1;i<=n;i++)
      if (hp[i]>0)
         score[i]+=hp[i]/2;
   for (i=1;i<=n;i++)
      printf("%ld %ld\n",hp[i],score[i]);
   return 0;
}
