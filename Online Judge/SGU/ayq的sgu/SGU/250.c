#include <stdio.h>
#define oo 10000

unsigned char l[3][182][182][182]={'\0'},max[2][182][182][182]={'\0'};
long map[181][181]={0},s[181][181]={0};
unsigned short f[3][182][182][182]={0};

int main()
{
   long i,j,k,n,m,a,pk,pi,pj,ans=-oo;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         scanf("%ld",&map[i][j]);
         s[i][j]=map[i][j]+s[i][j-1];
      }
   for(k=1;k<=n;k++)
      for(i=1;i<=m;i++)
         for(j=i;j<=m&&!(s[k][j]-s[k][i-1]);j++)
            if (f[0][k-1][i][j])
            {
               f[0][k][i][j]=f[0][k-1][i][j]+j-i+1;
               l[0][k][i][j]=l[0][k-1][i][j];
            }
            else
            {
               f[0][k][i][j]=j-i+1;
               l[0][k][i][j]=k-1;
            }
   for(k=1;k<=n;k++)
      for(i=1;i<=m;i++)
         for(j=m;j>=i;j--)
            if(f[0][k][i][j+1]>f[0][k][i][j])
            {
               f[0][k][i][j]=f[0][k][i][j+1];
               max[0][k][i][j]=max[0][k][i][j+1];
            }
            else
               max[0][k][i][j]=j;
   for(k=1;k<=n;k++)
      for(i=1;i<m;i++)
         for(j=i;j<m&&!(s[k][j]-s[k][i-1]);j++)
            if (f[1][k-1][i][j]>f[0][k-1][i][j+1])
            {
               f[1][k][i][j]=f[1][k-1][i][j]+j-i+1;
               l[1][k][i][j]=l[1][k-1][i][j];
            }
            else if (f[0][k-1][i][j+1])
            {
               f[1][k][i][j]=f[0][k-1][i][j+1]+j-i+1;
               l[1][k][i][j]=k-1;
            }
   for(k=1;k<=n;k++)
      for(i=1;i<m;i++)
         for(j=i;j<m;j++)
            if(f[1][k][i][j-1]>f[1][k][i][j])
            {
               f[1][k][i][j]=f[1][k][i][j-1];
               max[1][k][i][j]=max[1][k][i][j-1];
            }
            else
               max[1][k][i][j]=j;
   for(k=1;k<=n;k++)
      for(i=1;i<=m;i++)
         for(j=i;j<=m&&!(s[k][j]-s[k][i-1]);j++)
         {
            if (f[2][k-1][i][j]>f[1][k-1][i][j-1])
            {
               f[2][k][i][j]=f[2][k-1][i][j]+j-i+1;
               l[2][k][i][j]=l[2][k-1][i][j];
            }
            else if (f[1][k-1][i][j-1])
            {
               f[2][k][i][j]=f[1][k-1][i][j-1]+j-i+1;
               l[2][k][i][j]=k-1;
            }
            if (f[2][k][i][j]>ans)
            {
               ans=f[2][k][i][j];
               pk=k;
               pi=i;
               pj=j;
            }
         }
   if (ans<5)
      printf("-1\n");
   else
   {
      printf("%ld\n",ans);
      for (i=l[2][pk][pi][pj]+1;i<=pk;i++)
         for (j=pi;j<=pj;j++)
            map[i][j]=8;
      pk=l[2][pk][pi][pj];
      pj=max[1][pk][pi][pj-1];
      for (i=l[1][pk][pi][pj]+1;i<=pk;i++)
         for (j=pi;j<=pj;j++)
            map[i][j]=8;
      pk=l[1][pk][pi][pj];
      pj=max[0][pk][pi][pj+1];
      for (i=l[0][pk][pi][pj]+1;i<=pk;i++)
         for (j=pi;j<=pj;j++)
            map[i][j]=8;
      for (i=1;i<=n;i++)
         for (j=1;j<=m;j++)
            printf("%ld%c",map[i][j],(j==m)?'\n':' ');
   }
   return 0;
}
