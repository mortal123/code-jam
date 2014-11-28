#include<stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))

long ans[41]={0},a[101]={0},mat[101][102]={0},prime[101]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541};

int main()
{
   long i,j,k,n,m,t,px,py;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld",&a[i]);
      t=a[i];
      for (j=1;j<=n;j++)
         while (t%prime[j]==0)
         {
            mat[j][i]^=1;
            t/=prime[j];
         }
   }
   for (i=1;i<=min(n,m);i++)
   {
      for (j=i;j<=n;j++)
         for (k=i;k<=m;k++)
            if (mat[j][k])
            {
               px=j;
               py=k;
               goto out;
            }
      break;
      out:
      for (j=1;j<=m+1;j++)
      {
         t=mat[i][j];
         mat[i][j]=mat[px][j];
         mat[px][j]=t;
      }
      for (j=1;j<=n;j++)
      {
         t=mat[j][i];
         mat[j][i]=mat[j][py];
         mat[j][py]=t;
      }
      for (j=i+1;j<=n;j++)
         if (mat[j][i])
            for (k=i;k<=m+1;k++)
               mat[j][k]^=mat[i][k];
   }
   ans[1]=1;
   for (j=1;j<=m-i+1;j++)
      for (k=1;k<=40;k++)
      {
         ans[k]=ans[k]*2+ans[k-1]/10;
         ans[k-1]%=10;
      }
   for (i=1;i<=40;i++)
   {
      if (ans[i]>0)
      {
         ans[i]--;
         break;
      }
      else
         ans[i]=9;
   }
   for (i=40,j=0;i>=1;i--)
   {
      if (ans[i])
         j=1;
      if (j)
         printf("%ld",ans[i]);
   }
   if (!j)
      printf("0");
   printf("\n");
   return 0;
}
