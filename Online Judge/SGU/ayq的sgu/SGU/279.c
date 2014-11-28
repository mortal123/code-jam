#include <stdio.h>

long a[1001]={0},d[1001]={0},ans[2001]={0};
char hash[1001]={'\0'};

int main()
{
   long i,j,n,st=1,en=0,tot;
   scanf("%ld",&n);
   tot=2*n;
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   for (i=1;i<=n;i++)
   {
      re:
      for (j=1;j<=n&&(a[j]||hash[j]);j++);
      if (j<=n)
      {
         hash[j]=1;
         d[++en]=ans[tot--]=j;
         for (j--;j>=1;j--)
            a[j]--;
      }
      else if (st<=en)
      {
         for (j=d[st]+1;j<=n;j++)
            a[j]--;
         ans[tot--]=-d[st++];
         goto re;
      }
      else
         break;
   }
   if (i<=n)
      printf("NO\n");
   else
   {
      while (st<=en)
         ans[tot--]=-d[st++];
      printf("YES\n");
      for (i=1;i<=2*n;i++)
         printf("%ld%c",ans[i],(i==2*n)?'\n':' ');
   }
   return 0;
}
