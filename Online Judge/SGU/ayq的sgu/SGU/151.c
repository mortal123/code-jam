#include <stdio.h>
#include <math.h>
#define max(a,b) ((a)>(b)?(a):(b))

int main()
{
   double b,c,m,cosa,x1,y1,x2,y2;
   scanf("%lf%lf%lf",&c,&b,&m);
   if (b+c<=2*m-1e-7||2*m+b<=c-1e-7||2*m+c<=b-1e-7)
      printf("Mission impossible\n");
   else
   {
      cosa=(b*b+4*m*m-c*c)/(4*b*m);
      x1=cosa*b;
      y1=sqrt(max(b*b-x1*x1,0));
      x2=2*m-x1;
      y2=-y1;
      printf("%.5lf %.5lf\n%.5lf %.5lf\n%.5lf %.5lf\n",2*m,0.0,x1,y1,x2,y2);
   }
   return 0;
}
