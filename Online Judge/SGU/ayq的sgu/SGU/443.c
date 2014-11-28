#include<stdio.h>

char hash[1000001]={'\0'};
long prime[200001]={0};
long tot=0;

long work(long now)
{
   long i,p,s=0;
   for (i=1;i<=tot;i++)
      if (now%prime[i]==0)
      {
         s-=prime[i];
         p=prime[i];
      }
   s+=(p<<1);
   return s;
}

int main()
{
   long i,j,a,b;
   for (i=2;i<=1000000;i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=1000000;j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   scanf("%ld%ld",&a,&b);
   if (work(a)>work(b))
      printf("a\n");
   else
      printf("b\n");
   return 0;
}
