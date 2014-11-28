#include<stdio.h>

long x[1001]={0},hash[1001]={0};

int main()
{
   long a,b,c,m,k,i;
   scanf("%ld%ld%ld%ld%ld%ld",&x[0],&a,&b,&c,&m,&k);
   if (!k)
      printf("%ld\n",x[0]);
   else
   {
      x[0]%=m;
      hash[x[0]]=1;
      for (i=1;i<=k;i++)
      {
         x[i]=(a*x[i-1]*x[i-1]+b*x[i-1]+c)%m;
         if (hash[x[i]])
         {
           printf("%ld\n",x[hash[x[i]]+(k-hash[x[i]]+1)%(i+1-hash[x[i]])-1]);
           break;
         }
         hash[x[i]]=i+1;
      }
      if (i>k)
         printf("%ld\n",x[k]);
   }
   return 0;
}

