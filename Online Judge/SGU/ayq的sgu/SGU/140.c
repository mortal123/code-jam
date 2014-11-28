#include<stdio.h>

long last[10001]={0},laste[10001]={0},a[101]={0},time[101]={0},d[10001]={0};
char hash[10001]={'\0'};

int main()
{
   long i,j,n,p,b,now,st=1,en=1;
   scanf("%ld%ld%ld",&n,&p,&b);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   hash[0]=1;
   while (st<=en)
   {
      now=d[st++];
      for (i=1;i<=n;i++)
         if (!hash[(now+a[i])%p])
         {
            hash[(now+a[i])%p]=1;
            last[(now+a[i])%p]=now;
            laste[(now+a[i])%p]=i;
            d[++en]=(now+a[i])%p;
         }
   }
   if (!laste[b]&&b)
      printf("NO\n");
   else
   {
      printf("YES\n");
      for (i=b;laste[i];i=last[i])
         time[laste[i]]++;
      for (i=1;i<=n;i++)
         printf("%ld%c",time[i],(i==n)?'\n':' ');
   }
   return 0;
}
