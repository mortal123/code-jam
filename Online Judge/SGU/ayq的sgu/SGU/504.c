#include <stdio.h>
#define min(a,b) ((a)>(b)?(a):(b))

long hash1[702][702]={0},hash2[702][702]={0},hash3[702][702]={0},hash4[702][702]={0};
char map[702][702]={0};
long n,m,minx,maxx,miny,maxy;

long ok(long x,long y,long d)
{
   long i,j;
   for (i=1;i<=d/2;i++)
      for (j=1;j<=d;j++)
         if (map[x+i-1][y+j-1]!=map[x+d-i][y+j-1]||map[x+j-1][y+i-1]!=map[x+j-1][y+d-i])
            return 0;
   return 1;
}

long check(long w)
{
   long i,j,s=1,ss=1;
   for (i=1;i<w;i++)
      s*=29;
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=w;j++)
         hash1[i][j]=hash1[i][j-1]*29+map[i][j]-'a';
      for (j=w+1;j<=m;j++)
         hash1[i][j]=(hash1[i][j-1]-s*(map[i][j-w]-'a'))*29+map[i][j]-'a';
      for (j=m;j>m-w;j--)
         hash2[i][j]=hash2[i][j+1]*29+map[i][j]-'a';
      for (j=m-w;j>=1;j--)
         hash2[i][j]=(hash2[i][j+1]-s*(map[i][j+w]-'a'))*29+map[i][j]-'a';
   }
   s*=29;
   for (i=1;i<w;i++)
      ss*=s;
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         if (j>=w)
            hash3[i][j]=(hash3[i-1][j]-((i>w)?ss*hash1[i-w][j]:0))*s+hash1[i][j];
         if (j<=m-w+1)
            hash4[i][j]=(hash4[i-1][j]-((i>w)?ss*hash2[i-w][j]:0))*s+hash2[i][j];
      }
   for (i=1;i<=n-w+1;i++)
      for (j=1;j<=m-w+1;j++)
         if (hash3[i+w-1][j+w-1]==hash4[i+w-1][j]&&ok(i,j,w))
         {
            minx=i;
            miny=j;
            maxx=i+w-1;
            maxy=j+w-1;
            return 1;
         }
   return 0;
}

int main()
{
   long i,l=0,r,mid,ans;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
      gets(map[i]+1);
   r=min(n,m)/2+1;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (check(mid+mid))
         l=mid;
      else
         r=mid;
   }
   ans=l+l;
   l=0;
   r=(min(n,m)+1)/2+1;
   while (l<r-1)
   {
      mid=(l+r)>>1;
      if (check(mid+mid+1))
         l=mid;
      else
         r=mid;
   }
   if (l+l+1>ans)
      ans=l+l+1;
   check(ans);
   printf("%ld %ld %ld %ld\n",minx,miny,maxx,maxy);
   return 0;
}
