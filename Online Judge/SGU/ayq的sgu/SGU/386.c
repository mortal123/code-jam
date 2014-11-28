#include <stdio.h>

int a[51][51],rec[51];
double b[51][51];
int p;

int mi(int a,int b)
{
   int t;
   if (!b)
      return 1;
   t=mi(a,b>>1);
   t=t*t%p;
   if(b&1)
      t=t*a%p;
   return t;
}

int main()
{
   int i,j,k,n,ans=0,s=1,ans2=0;
   double t;
   scanf("%d%d",&n,&p);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         scanf("%d",&a[i][j]);
         b[i][j]=a[i][j];
      }
   for (i=1;i<=n;i++)
   {
      if (!a[i][i])
      {
         for (j=i+1;j<=n&&!a[j][i];j++);
         if (j>n)
            goto out;
         rec[i]=j;
         for (j=i;j<=n;j++)
         {
            a[i][j]^=a[rec[i]][j];
            a[rec[i]][j]^=a[i][j];
            a[i][j]^=a[rec[i]][j];
        }
      }
      for (j=i+1;j<=n;j++)
      {
         s=s*a[i][i]%p;
         for (k=i+1;k<=n;k++)
            a[j][k]=((a[j][k]*a[i][i]-a[i][k]*a[j][i])%p+p)%p;
      }
   }
   ans=mi(s,p-2);
   for (i=1;i<=n;i++)
      ans=ans*2*a[i][i]%p;
   for (i=1;i<=n;i++)
   {
      if (rec[i])
         for (j=i;j<=n;j++)
         {
            t=b[i][j];
            b[i][j]=b[rec[i]][j];
            b[rec[i]][j]=t;
        }
      ans2^=(b[i][i]<0);
      for (j=i+1;j<=n;j++)
         for (k=i+1;k<=n;k++)
            b[j][k]-=b[i][k]*b[j][i]/b[i][i];
   }
   if (ans2)
      ans=p-ans;
   out:
   printf("%d\n",ans);
   return 0;
}
