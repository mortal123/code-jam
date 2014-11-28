#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

long f[101][11][11][11][11]={0},a[11]={0},b[11]={0};
long m,n;

long dp(long m,long p1,long p2,long p3,long p4)
{
   long i,t;
   if (m<=0)
      return 0;
   if (f[m][p1][p2][p3][p4])
      return f[m][p1][p2][p3][p4];
   f[m][p1][p2][p3][p4]=oo;
   for (i=1;i<=n;i++)
      if ((p1!=i||b[i]!=4)&&(p2!=i||b[i]<=2)&&(p3!=i||b[i]<=1)&&(p4!=i||!b[i]))
      {
         t=dp(m-a[i],p2,p3,p4,i)+1;
		 f[m][p1][p2][p3][p4]=min(f[m][p1][p2][p3][p4],t);
	  }
   if (f[m][p1][p2][p3][p4]==oo)
      f[m][p1][p2][p3][p4]=dp(m,p2,p3,p4,0)+1;
   return f[m][p1][p2][p3][p4];
}

int main()
{
   long i;
   scanf("%ld%ld",&m,&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&a[i],&b[i]);
      if (!a[i])
      {
         n--;
         i--;
      }
   }
   printf("%ld\n",dp(m,0,0,0,0));
   return 0;
}
