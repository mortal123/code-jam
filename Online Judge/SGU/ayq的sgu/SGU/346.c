#include<stdio.h>

long p[8]={0};
char str[10]={'\0'};

int main()
{
   long i,m,ans=0;
   for (i=1;i<=7;i++)
   {
      scanf("%ld",&p[i]);
      if (p[i])
         m=i;
   }
   scanf("%s",str+1);
   if (str[1]=='R')
      ans+=m;
   ans+=p[1]*(m+1);
   for (i=2;i<=7;i++)
      ans+=p[i]*i;
   printf("%ld\n",ans);
   return 0;
}
