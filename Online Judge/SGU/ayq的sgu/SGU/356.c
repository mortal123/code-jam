#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long f[101][1001]={0},l[101]={0},prime[101]={0},num[101]={0},x[1001]={0};
char hash[101]={0};

int main()
{
   long i,j,a,t,n,k,tot=0,lx=1;
   l[0]=f[0][1]=x[1]=1;
   scanf("%ld%ld",&k,&n);
   if (k==n-1)
   {
      puts("0");
      goto end;
   }
   for (i=2;i<=n-k;i++)
   {
      l[i]=max(l[i-1],l[i-2])+3;
      for (j=1;j<=l[i];j++)
      {
         f[i][j]=(f[i-1][j]+f[i-2][j])*(i-1)+f[i][j-1]/10;
         f[i][j-1]%=10;
      }
      while (!f[i][l[i]])
         l[i]--;
   }
   for (i=2;i<=max(k,n-k);i++)
   {
      if (!hash[i])
         prime[++tot]=i;
      for (j=1;prime[j]*i<=max(k,n-k);j++)
      {
         hash[prime[j]*i]=1;
         if (i%prime[j]==0)
            break;
      }
   }
   for (i=1;i<=tot;i++)
      for (j=prime[i];j<=k;j*=prime[i])
         num[i]+=k/j;
   for (i=1;i<=tot;i++)
      for (j=prime[i];j<=n-k;j*=prime[i])
         num[i]+=(n-k)/j;
   for (i=1;i<=tot;i++)
      for (j=1;j<=num[i];j++)
      {
         t=0;
         for (a=l[n-k];a>=1;a--)
            t=(t*10+f[n-k][a])%prime[i];
         if (!t)
         {
            for (a=l[n-k]-1;a>=0;a--)
            {
               f[n-k][a]+=f[n-k][a+1]%prime[i]*10;
               f[n-k][a+1]/=prime[i];
            }
            while (!f[n-k][l[n-k]])
               l[n-k]--;
         }
         else
         {
            lx+=3;
            for (a=1;a<=lx;a++)
            {
               x[a]=x[a]*prime[i]+x[a-1]/10;
               x[a-1]%=10;
            }
            while (!x[lx])
               lx--;
         }
      }
   for (i=l[n-k];i>=1;i--)
      printf("%ld",f[n-k][i]);
   printf("/");
   for (i=lx;i>=1;i--)
      printf("%ld",x[i]);
   puts("");
   end:
   return 0;
}
