#include<stdio.h>
#define lowbit(a) ((a)&(-(a)))

long long f[11][1025][101]={0};
long cnt[1025]={0};

int main()
{
   long i,j,k,l,t,n,m;
   long long ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=0;i<(1<<n);i++)
   {
      t=i;
      while (t)
      {
         t-=lowbit(t);
         cnt[i]++;
      }
   }
   f[0][0][0]=1;
   for (i=1;i<=n;i++)
      for (j=0;j<(1<<n);j++)
         if (!(j&(j>>1))&&!(j&(j<<1)))
            for (k=0;k<(1<<n);k++)
               if (!(k&(k>>1))&&!(k&(k<<1))&&!(j&k)&&!(j&(k>>1))&&!(j&(k<<1)))
                  for (l=cnt[j];l<=m;l++)
                     f[i][j][l]+=f[i-1][k][l-cnt[j]];
   for (i=0;i<(1<<n);i++)
      ans+=f[n][i][m];
   printf("%I64d\n",ans);
   return 0;
}

