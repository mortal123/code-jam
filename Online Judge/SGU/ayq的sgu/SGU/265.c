#include <stdio.h>
#include <math.h>
#define pi 3.14159265359

struct case1
{
   double x,y,z;
}p[4]={{0,0,0}};
char str[51]={'\0'};

double read(long *l)
{
   char sign=0,flag=0;
   double x=0,y=1;
   if (str[*l]=='-')
   {
      sign=1;
      (*l)++;
   }
   for (;str[*l]!=' '&&str[*l];(*l)++)
      if (str[*l]=='.')
         flag=1;
      else
      {
         x=x*10+str[*l]-'0';
         if (flag)
            y*=10;
      }
   if (sign)
      x=-x;
   (*l)++;
   return x/y;
}

int main()
{
   char sign;
   long i,j,n;
   double a,b,c,d,x,y,z,t,cosd,sind;
   scanf("%ld\n",&n);
   p[1].x=p[2].y=p[3].z=1;
   for (i=1;i<=n;i++)
   {
      scanf("%c",&sign);
      if (sign=='T')
      {
         scanf("%lf%lf%lf\n",&a,&b,&c);
         for (j=0;j<=3;j++)
         {
            p[j].x+=a;
            p[j].y+=b;
            p[j].z+=c;
         }
      }
      else if (sign=='S')
      {
         scanf("%lf%lf%lf\n",&a,&b,&c);
         for (j=0;j<=3;j++)
         {
            p[j].x*=a;
            p[j].y*=b;
            p[j].z*=c;
         }
      }
      else
      {
         scanf("%lf%lf%lf%lf\n",&a,&b,&c,&d);
         t=sqrt(a*a+b*b+c*c);
         a/=t;
         b/=t;
         c/=t;
         cosd=cos((-d/180)*pi);
         sind=sin((-d/180)*pi);
         for (j=0;j<=3;j++)
         {
            x=p[j].x;
            y=p[j].y;
            z=p[j].z;
            p[j].x=x*(cosd+(1-cosd)*a*a)+y*((1-cosd)*a*b+sind*c)+z*((1-cosd)*a*c-sind*b);
            p[j].y=x*((1-cosd)*a*b-sind*c)+y*(cosd+(1-cosd)*b*b)+z*((1-cosd)*b*c+sind*a);
            p[j].z=x*((1-cosd)*a*c+sind*b)+y*((1-cosd)*b*c-sind*a)+z*(cosd+(1-cosd)*c*c);
         }
      }
   }
   for (i=1;i<=3;i++)
   {
      p[i].x-=p[0].x;
      p[i].y-=p[0].y;
      p[i].z-=p[0].z;
   }
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      j=1;
      a=read(&j);
      b=read(&j);
      c=read(&j);
      printf("%lf %lf %lf\n",p[0].x+a*p[1].x+b*p[2].x+c*p[3].x+1e-10,p[0].y+a*p[1].y+b*p[2].y+c*p[3].y+1e-10,p[0].z+a*p[1].z+b*p[2].z+c*p[3].z+1e-10);
   }
   return 0;
}
