#include<stdio.h>

long list[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{
   long i,n,m,s;
   scanf("%ld%ld",&m,&n);
   if (n<=0||n>=13||list[n]<m)
      printf("Impossible\n");
   else
   {
      s=m;
      for (i=1;i<n;i++)
         s+=list[i];
      printf("%ld\n",(s-1)%7+1);
   }
   return 0;
}
