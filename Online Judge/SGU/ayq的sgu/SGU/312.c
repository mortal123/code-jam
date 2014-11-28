#include <stdio.h>
#include <math.h>
#define eps 1e-10
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(a,b,c) ((p[b].x-p[a].x)*(p[c].y-p[a].y)-(p[c].x-p[a].x)*(p[b].y-p[a].y))
#define dis(a,b) sqrt((p[a].x-p[b].x)*(p[a].x-p[b].x)+(p[a].y-p[b].y)*(p[a].y-p[b].y))

struct case1
{
  double x,y;
}p[7];
struct case2
{
   double x1,y1,x2,y2;
};
int K[5];

struct case2 solve2(int a,int b,double dis)
{
   double ux=(p[b].x-p[a].x)/dis(a,b),uy=(p[b].y-p[a].y)/dis(a,b);
   return (struct case2){p[a].x-uy*dis,p[a].y+ux*dis,p[b].x-uy*dis,p[b].y+ux*dis};
}

struct case1 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case1 t;
   double k1,b1,k2,b2;
   if (zero(a-c))
   {
      t.x=a;
      t.y=h+(f-h)*(a-g)/(e-g);
   }
   else if (zero(e-g))
   {
      t.x=e;
      t.y=d+(b-d)*(e-c)/(a-c);
   }
   else
   {
      k1=(d-b)/(c-a);
      k2=(h-f)/(g-e);
      b1=(b*c-a*d)/(c-a);
      b2=(f*g-e*h)/(g-e);
      t.x=(b2-b1)/(k1-k2);
      t.y=k1*t.x+b1;
   }
   return t;
}

int main()
{
   int i,n,sk;
   struct case2 a,b;
   double x,y,s=0;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf",&p[i].x,&p[i].y);
   scanf("%d",&K[1]);
   sk=K[1];
   for (i=2;i<=n;i++)
   {
      scanf(":%d",&K[i]);
      sk+=K[i];
   }
   for (i=2;i<n;i++)
      s+=cj(1,i,i+1);
   if (s<0)
   {
      p[0]=p[2];
      p[2]=p[n];
      p[n]=p[0];
      for (i=1;i<=n/2;i++)
      {
         K[i]^=K[n-i+1];
         K[n-i+1]^=K[i];
         K[i]^=K[n-i+1];
      }
   }
   if (n==3)
   {
      p[0]=p[1];
      for (i=1;i<=n;i++)
      {
         p[i].x-=p[0].x;
         p[i].y-=p[0].y;
      }
      x=abb(s)*(K[1]*p[3].x+K[3]*p[2].x)/sk/(p[3].y*p[2].x-p[2].y*p[3].x);
      y=abb(s)*(K[1]*p[3].y+K[3]*p[2].y)/sk/(p[3].y*p[2].x-p[2].y*p[3].x);
      if (s<0)
      {
         p[5]=p[2];
         p[2]=p[3];
         p[3]=p[5];
      }
      for (i=1;i<=3;i++)
         printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x+p[0].x,p[i].y+p[0].y,p[i%3+1].x+p[0].x,p[i%3+1].y+p[0].y,x+p[0].x,y+p[0].y);
   }
   else
   {
      for (i=1;cj(i,i+2,i+1)*cj(i,i+2,7-3*i)>0;i++);
      if (cj(i+1,i+2,i)>abb(s)*(K[i]+K[i+1])/sk+eps)
      {
         a=solve2(i+2,i,(cj(i+1,i+2,i)-abb(s)*(K[i]+K[i+1])/sk)/dis(i,i+2));
         b=solve2(i+1,i+2,abb(s)*K[i+1]/sk/dis(i+1,i+2));
         p[5]=solve(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1,b.x2,b.y2);
         a=solve2(7-3*i,5,(abb(s)*K[7-3*i]/sk+cj(7-3*i,5,i))/dis(7-3*i,5));
         p[6]=solve(a.x1,a.y1,a.x2,a.y2,p[i+2].x,p[i+2].y,p[i].x,p[i].y);
         if (s>0)
         {
            if (i==2)
               printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[5].x,p[5].y,p[6].x,p[6].y);   
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[i+1].x,p[i+1].y,p[5].x,p[5].y);
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+1].x,p[i+1].y,p[i+2].x,p[i+2].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+2].x,p[i+2].y,p[7-3*i].x,p[7-3*i].y,p[6].x,p[6].y,p[5].x,p[5].y);
            if (i==1)
               printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[5].x,p[5].y,p[6].x,p[6].y);
         }
         else
         {
            if (i==1)
               printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[7-3*i].x,p[7-3*i].y,p[6].x,p[6].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i+2].x,p[i+2].y,p[5].x,p[5].y,p[6].x,p[6].y);
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+2].x,p[i+2].y,p[i+1].x,p[i+1].y,p[5].x,p[5].y);
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+1].x,p[i+1].y,p[i].x,p[i].y,p[5].x,p[5].y);
            if (i==2)
               printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[7-3*i].x,p[7-3*i].y,p[6].x,p[6].y,p[5].x,p[5].y);
         }
      }
      else if (cj(i+1,i+2,i)<abb(s)*(K[i]+K[i+1])/sk-eps)
      {
         a=solve2(i,i+2,(cj(7-3*i,i,i+2)-abb(s)*(K[i+2]+K[7-3*i])/sk)/dis(i,i+2));
         b=solve2(i+2,7-3*i,abb(s)*K[i+2]/sk/dis(i+2,7-3*i));
         p[5]=solve(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1,b.x2,b.y2);
         a=solve2(i+1,5,(cj(i+1,5,i)-abb(s)*K[i]/sk)/dis(i+1,5));
         p[6]=solve(a.x1,a.y1,a.x2,a.y2,p[i+2].x,p[i+2].y,p[i].x,p[i].y);
         if (s>0)
         {
            if (i==2)
               printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[i+1].x,p[i+1].y,p[6].x,p[6].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+1].x,p[i+1].y,p[i+2].x,p[i+2].y,p[5].x,p[5].y,p[6].x,p[6].y);
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+2].x,p[i+2].y,p[7-3*i].x,p[7-3*i].y,p[5].x,p[5].y);
            if (i==1)
               printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[5].x,p[5].y);
         }
         else
         {
            if (i==1)
               printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[7-3*i].x,p[7-3*i].y,p[5].x,p[5].y);
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i+2].x,p[i+2].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+2].x,p[i+2].y,p[i+1].x,p[i+1].y,p[6].x,p[6].y,p[5].x,p[5].y);
            printf("4 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+1].x,p[i+1].y,p[i].x,p[i].y,p[5].x,p[5].y,p[6].x,p[6].y);
            if (i==2)
               printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[7-3*i].x,p[7-3*i].y,p[5].x,p[5].y);
         }
      }
      else
      {
         a=solve2(i+2,i,(cj(i+1,i+2,i)-abb(s)*(K[i]+K[i+1])/sk)/dis(i,i+2));
         b=solve2(i+1,i+2,abb(s)*K[i+1]/sk/dis(i+1,i+2));
         p[5]=solve(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1,b.x2,b.y2);
         a=solve2(i,i+2,(cj(7-3*i,i,i+2)-abb(s)*(K[i+2]+K[7-3*i])/sk)/dis(i,i+2));
         b=solve2(i+2,7-3*i,abb(s)*K[i+2]/sk/dis(i+2,7-3*i));
         p[6]=solve(a.x1,a.y1,a.x2,a.y2,b.x1,b.y1,b.x2,b.y2);
         if (s<0)
         {
            p[0]=p[2];
            p[2]=p[4];
            p[4]=p[0];
            p[0]=p[5];
            p[5]=p[6];
            p[6]=p[0];
         }
         if (i==2)
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[6].x,p[6].y);
         printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i].x,p[i].y,p[i+1].x,p[i+1].y,p[5].x,p[5].y);
         printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+1].x,p[i+1].y,p[i+2].x,p[i+2].y,p[5].x,p[5].y);
         printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[i+2].x,p[i+2].y,p[7-3*i].x,p[7-3*i].y,p[6].x,p[6].y);
         if (i==1)
            printf("3 %.9lf %.9lf %.9lf %.9lf %.9lf %.9lf\n",p[7-3*i].x,p[7-3*i].y,p[i].x,p[i].y,p[6].x,p[6].y);
      }
   }
   return 0;
}
