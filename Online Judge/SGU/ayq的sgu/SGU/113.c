#include<stdio.h>

long p[20001]={0};
char hash[100001]={'\0'};

int main()
{
   long i,j,k,t,n,num,tot=0;
   for (i=2;i<=100000;i++)
   {
      if (!hash[i])
         p[++tot]=i;
      for (j=1;p[j]*i<=100000;j++)
      {
          hash[p[j]*i]=1;
          if (i%p[j]==0)
             break;
      }
   }
   scanf("%ld",&n);
   while (n--)
   {
      scanf("%ld",&k);
      t=k;
      num=0;
      for (i=1;p[i]*p[i]<=t;i++)
         while (k%p[i]==0)
         {
            num++;
            if (num>2)
               goto out;
            k/=p[i];
         }
      if (k>1)
         num++;
      out:
      if (num==2)
         printf("Yes\n");
      else
         printf("No\n");
   }
   return 0;
}
