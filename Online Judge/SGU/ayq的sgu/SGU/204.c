#include <stdio.h> 
#include <math.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define F(x) sqrt(-g/2*(1/(x)+(m+n)*(m+n)*(x)))

double b1,t1,b2,t2,l,ds,df,g;

double speed(double m,double n,double h1,double h2)
{
   double rec=min(F(-h2/m/n),F(-h1/m/n));
   if (1/(m+n)>h1/m/n&&1/(m+n)<h2/m/n)
      rec=min(rec,F(-1/(m+n)));
   return rec;
}

double work(double s)
{
   double p1=speed(ds,s,b1,t1),p2=speed(df,l-s,b2,t2);
   return max(p1,p2);
}

int main()
{
   long i;
   double left,right,a,b;
   while (scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&b1,&t1,&b2,&t2,&l,&ds,&df,&g)!=EOF)
   {
      left=0;
      right=l;
      while (right-left>1e-12)
      {
         a=(left*2+right)/3;
         b=(left+right*2)/3;
         if (work(a)>work(b))
            left=a;
         else
            right=b;
      }
      printf("%.10lf\n",work((right+left)/2));
   }
   return 0;
}
