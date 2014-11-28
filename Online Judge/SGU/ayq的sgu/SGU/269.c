#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long s[251]={0},f[251][251]={0},l[251]={0};

int main()
{
   long i,j,k,t,n,m;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      scanf("%ld",&s[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (s[i]>s[j])
         {
            t=s[i];
            s[i]=s[j];
            s[j]=t;
         }
   f[0][1]=1;
   for (i=0;i<=m;i++)
      l[i]=1;
   for (i=1;i<=n;i++)
      for (j=m;j>=1;j--)
         if (s[i]-j+1>0)
         {
            l[j]=max(l[j],l[j-1]);
            for (k=1;k<=l[j]+1;k++)
            {
               f[j][k]+=f[j-1][k]*(s[i]-j+1)+f[j][k-1]/100000;
               f[j][k-1]%=100000;
            }
            if (f[j][l[j]+1])
               l[j]++;
         }
   printf("%ld",f[m][l[m]]);
   for (i=l[m]-1;i>=1;i--)
      printf("%.5ld",f[m][i]);
   printf("\n");
   return 0;
}
