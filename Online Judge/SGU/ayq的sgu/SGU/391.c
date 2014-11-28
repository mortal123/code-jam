#include <stdio.h>

char hash1[100001],hash2[100001];

int check(char a[],int n)
{
   int i,j;
   for (i=1;i<=n;i=j+1)
   {
      j=i;
      while (j<n&&a[j+1]==a[j])
         j++;
      if (i>1&&j<n&&!((j-i)&1)&&(!a[i]||j>=i+2))
         return 0;
   }
   return 1;
}

int main()
{
   int i,j,n,m,k,x,y;
   scanf("%d%d%d",&n,&m,&k);
   for (i=1;i<=k;i++)
   {
      scanf("%d%d",&x,&y);
      hash1[x]=hash2[y]=1;
   }
   x=y=0;
   for (i=1;i<=n;i++)
      x+=hash1[i];
   for (i=1;i<=m;i++)
      y+=hash2[i];
   puts(((long long)x*y==k&&check(hash1,n)&&check(hash2,m))?"YES":"NO");
   return 0;
}
