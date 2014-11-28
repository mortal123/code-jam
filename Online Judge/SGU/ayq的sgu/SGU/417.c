#include<stdio.h>
#include<math.h>
#define pi 3.14159265358979323846

int main()
{
   long x,y,r;
   scanf("%ld%ld%ld",&x,&y,&r);
   printf("%.20lf",log(x*x+y*y)/log(2.718281828459)*r*r*pi);
   return 0;
}
