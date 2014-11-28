#include<stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long ans[101]={0},s1[110]={0},s2[110]={0},f1[2501][51]={0},f2[2501][51]={0};

void add(long a[],long b[],long c)
{
   long i;
   for (i=1;i<=50;i++)
      a[i]+=b[i]*c;
   for (i=2;i<=50;i++)
   {
      a[i]+=a[i-1]/10;
      a[i-1]%=10;
   }
}

void add2(long a[],long b[])
{
   long i,j;
   for (i=1;i<=50;i++)
      for (j=1;j<=50;j++)
         ans[i+j-1]+=a[i]*b[j];
   for (i=2;i<=100;i++)
   {
      ans[i]+=ans[i-1]/10;
      ans[i-1]%=10;
   }
}

int main()
{
   long i,j,k,t,n,m,s=0,tot1=0,tot2=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<2*n;i++)
   {
      s=0;
      for (j=1;j<=n;j++)
         if (i-j+1>=1&&i-j+1<=n)
            s++;
      if (i&1)
         s1[++tot1]=s;
      else
         s2[++tot2]=s;
   }
   for (i=1;i<tot1;i++)
      for (j=i+1;j<=tot1;j++)
         if (s1[j]<s1[i])
         {
            t=s1[j];
            s1[j]=s1[i];
            s1[i]=t;
         }
   for (i=1;i<tot2;i++)
      for (j=i+1;j<=tot2;j++)
         if (s2[j]<s2[i])
         {
            t=s2[j];
            s2[j]=s2[i];
            s2[i]=t;
         }
   f1[0][1]=1;
   for (i=1;i<=tot1;i++)
      for (j=m;j>=1;j--)
         add(f1[j],f1[j-1],max(s1[i]-j+1,0));
   f2[0][1]=1;
   for (i=1;i<=tot2;i++)
      for (j=m;j>=1;j--)
         add(f2[j],f2[j-1],max(s2[i]-j+1,0));
   for (i=0;i<=m;i++)
      add2(f1[i],f2[m-i]);
   for (i=100,j=0;i>=1;i--)
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
