#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

long f[9][73][10][10][2]={0},a[11]={0};
char hash[9][73][10][10][2]={0};
long tot,flag=0;

long count(long x)
{
   long s=0;
   while (x)
   {
      s++;
      x/=10;
   }
   return s;
}

long dp(long i,long j,long k,long l,long t)
{
   long x;
   if (i==2*tot+1)
      return j+k>=36&&j-l<=36&&j!=36;
   if (hash[i][j][k][l][t]==flag)
      return f[i][j][k][l][t];
   hash[i][j][k][l][t]=flag;
   f[i][j][k][l][t]=0;
   if (!t)
      for (x=(i==1);x<=a[i];x++)
         f[i][j][k][l][t]+=dp(i+1,j+(1-2*(i>tot))*x,max(k,(i>tot)?x-(i==1):9-x),max(l,(i>tot)?9-x:x-(i==1)),x<a[i]);
   else
      for (x=(i==1);x<=9;x++)
         f[i][j][k][l][t]+=dp(i+1,j+(1-2*(i>tot))*x,max(k,(i>tot)?x-(i==1):9-x),max(l,(i>tot)?9-x:x-(i==1)),1);
   return f[i][j][k][l][t];
}

long work(long x)
{
   long i,s,sum=0;
   if (x<10)
      return 0;
   s=count(x);
   if (x==1000000000)
   {
      sum=1;
      s--;
   }
   else if (!(s&1))
   {
      for (i=s;i>=1;i--)
      {
         a[i]=x%10;
         x/=10;
      }
      tot=s/2;
      flag++;
      sum+=dp(1,36,0,0,0);
      s--;
   }
   for (i=1;i<s;i++)
      a[i]=9;
   for (i=1;i<=s/2;i++)
   {
      tot=i;
      flag++;
      sum+=dp(1,36,0,0,0);
   }
   return sum;
}

int main()
{
   long a,b;
   scanf("%ld%ld",&a,&b);
   printf("%ld\n",work(b)-work(a-1));
   return 0;
}
