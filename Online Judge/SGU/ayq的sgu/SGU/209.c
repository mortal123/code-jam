#include<stdio.h>
#include<math.h>
#define oo 10000
#define pi 3.14159265359
#define zero(a) (abb(a)<=1e-6)
#define abb(a) ((a)>0?(a):(-(a)))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x1,y1,x2,y2;
}p[81]={{0,0,0,0}};
struct case2
{
   double x,y;
}d[6401]={{0,0}};
long head[6401]={0},next[12801]={0},e[12801]={0},rec[81]={0};
double area[6401]={0};
char hash[12801]={'\0'};
long node=0,totm=0,tota=0;

struct case2 solve(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case2 t;
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

long find(double x,double y)
{
   long i;
   for (i=1;i<=node;i++)
      if (zero(d[i].x-x)&&zero(d[i].y-y))
         return i;
   d[++node].x=x;
   d[node].y=y;
   return node;
}

void add(long a,long b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

double D(double x,double y)
{
   if (x>1e-6&&y>=0)
      return atan(y/x);
   if (x<-1e-6)
      return pi+atan(y/x);
   if (x>1e-6&&y<0)
      return 2*pi-atan(-y/x);
   if (y>0)
      return pi/2;
   return pi/2*3;
}

void walk(long st,long last,long now,double sum)
{
   long i,t;
   double s=D(d[last].x-d[now].x,d[last].y-d[now].y),min=oo,temp;
   for (i=head[now];i;i=next[i])
   {
      temp=D(d[e[i]].x-d[now].x,d[e[i]].y-d[now].y)-s;
      if (temp<1e-7)
         temp+=2*pi;
      if (temp<min)
      {
         min=temp;
         t=i;
      }
   }
   hash[t]=1;
   if (e[t]==st)
      area[++tota]=sum;
   else if (min<pi)
      walk(st,now,e[t],sum+cj(d[e[t]].x-d[st].x,d[e[t]].y-d[st].y,d[now].x-d[st].x,d[now].y-d[st].y)/2);
}

int main()
{
   long i,j,k,n,temp,tot;
   struct case2 t;
   double temp2;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%lf%lf%lf%lf",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
   for (i=1;i<=n;i++)
   {
      tot=0;
      for (j=1;j<=n;j++)
         if (i!=j&&!zero((p[i].x2-p[i].x1)*(p[j].y2-p[j].y1)-(p[j].x2-p[j].x1)*(p[i].y2-p[i].y1)))
         {
            t=solve(p[i].x1,p[i].y1,p[i].x2,p[i].y2,p[j].x1,p[j].y1,p[j].x2,p[j].y2);
            rec[++tot]=find(t.x,t.y);
         }
      for (j=1;j<tot;j++)
         for (k=j+1;k<=tot;k++)
            if (d[rec[k]].x<=d[rec[j]].x-1e-6||zero(d[rec[j]].x-d[rec[k]].x)&&d[rec[k]].y<=d[rec[j]].y-1e-6)
            {
               temp=rec[j];
               rec[j]=rec[k];
               rec[k]=temp;
            }
      for (j=1;j<tot;j++)
         if (rec[j]!=rec[j+1])
         {
            add(rec[j],rec[j+1]);
            add(rec[j+1],rec[j]);
         }
   }
   for (i=1;i<=node;i++)
      for (j=head[i];j;j=next[j])
         if (!hash[j])
         {
            hash[j]=1;
            walk(i,i,e[j],0);
         }
   for (i=1;i<tota;i++)
      for (j=i+1;j<=tota;j++)
         if (area[i]>area[j])
         {
            temp2=area[i];
            area[i]=area[j];
            area[j]=temp2;
         }
   printf("%ld\n",tota);
   for (i=1;i<=tota;i++)
      printf("%.4lf\n",area[i]);
   return 0;
}
