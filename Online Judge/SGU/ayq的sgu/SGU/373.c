#include <stdio.h>
#include <math.h>
#define eps 1e-8
#define zero(a) (abb(a)<=1e-6)
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define pi 3.1415926535897932384626433832795
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

struct case1
{
   double x,y;
}p[12][12],p2[12][12];
int mi[12],link[12][12],tot[12],link2[12][12],tot2[12];
double f[177147],area[12];
char hash[177147];
int o=1;

double dfs(int now,double t)
{
   int a[12];
   int i,x=now;
   double tmp,s=0;
   if (hash[now])
      return f[now];
   hash[now]=1;
   for (i=1;i<=o;i++)
   {
      a[i]=x%3;
      x/=3;
      if (!a[i])
         s+=area[i];
   }
   for (i=1;i<=o;i++)
      if (!a[i])
      {
         tmp=dfs(now+(1+(t<eps))*mi[i],t+(2*(t<eps)-1)*area[i]);
         if ((t+(2*(t<eps)-1)*area[i]<eps)^(t<eps))
            f[now]=max(f[now],s-tmp);
         else
            f[now]=max(f[now],tmp+area[i]);
      }
   return f[now];
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
   double A,B,C,t,x1,y1,x2,y2,r,drt,px1,py1,px2,py2;
   int i,j,k,a,b,c,n,o2,now,cur,flag;
   struct case1 tmp;
   scanf("%d%lf",&n,&r);
   tot[1]=2;
   p[1][1]=p[1][3]=(struct case1){-r,0};
   p[1][2]=(struct case1){r,0};
   link[1][1]=link[1][2]=mi[1]=1;
   for (i=2;i<=11;i++)
      mi[i]=mi[i-1]*3;
   for (i=1;i<=n;i++)
   {
      scanf("%d%d%d",&a,&b,&c);
      if (!b)
      {
         x1=x2=-1.0*c/a;
         y1=-r;
         y2=r;
      }
      else
      {
         x1=-r;
         x2=r;
         y1=(-1.0*a*x1-c)/b;
         y2=(-1.0*a*x2-c)/b;
      }
      o2=0;
      for (j=1;j<=o;j++)
      {
         flag=0;
         tot2[cur=++o2]=0;
         for (k=1;k<=tot[j];k++)
         {
            now=(flag?o2:cur);
            p2[now][++tot2[now]]=p[j][k];
            link2[now][tot2[now]]=link[j][k];
            if (link[j][k])
            {
               if (!b)
               {
                  px1=px2=x1;
                  py1=sqrt(r*r-px1*px1);
                  py2=-py1;
               }
               else
               {
                  A=1+1.0*a*a/b/b;
                  B=2.0*a*c/b/b;
                  C=1.0*c*c/b/b-r*r;
                  drt=B*B-4*A*C;
                  px1=(-B+sqrt(drt))/2/A;
                  px2=(-B-sqrt(drt))/2/A;
                  py1=(-a*px1-c)/b;
                  py2=(-a*px2-c)/b;
               }
               if ((cj(p[j][k].x,p[j][k].y,px1,py1)>-eps&&cj(px1,py1,p[j][k+1].x,p[j][k+1].y)>eps||zero(p[j][k].x-px1)&&zero(p[j][k].y-py1))&&(cj(p[j][k].x,p[j][k].y,px2,py2)>-eps&&cj(px2,py2,p[j][k+1].x,p[j][k+1].y)>eps||zero(p[j][k].x-px2)&&zero(p[j][k].y-py2)))
               {
                  if (cj(px1,py1,px2,py2)<0)
                  {
                     t=px1;
                     px1=px2;
                     px2=t;
                     t=py1;
                     py1=py2;
                     py2=t;
                  }
                  p2[cur][++tot2[cur]]=(struct case1){px1,py1};
                  link2[cur][tot2[cur]]=0;
                  p2[cur][++tot2[cur]]=(struct case1){px2,py2};
                  link2[cur][tot2[cur]]=1;
                  tot2[++o2]=2;
                  p2[o2][1]=(struct case1){px1,py1};
                  link2[o2][1]=1;
                  p2[o2][2]=(struct case1){px2,py2};
                  link2[o2][2]=0;
               }
               else
               {
                  if (cj(p[j][k].x,p[j][k].y,px2,py2)>-eps&&cj(px2,py2,p[j][k+1].x,p[j][k+1].y)>eps||zero(p[j][k].x-px2)&&zero(p[j][k].y-py2))
                  {
                     px1=px2;
                     py1=py2;
                  }
                  if (cj(p[j][k].x,p[j][k].y,px1,py1)>-eps&&cj(px1,py1,p[j][k+1].x,p[j][k+1].y)>eps||zero(p[j][k].x-px1)&&zero(p[j][k].y-py1))
                     if (!flag)
                     {
                        p2[cur][++tot2[cur]]=(struct case1){px1,py1};
                        tot2[++o2]=link2[cur][tot2[cur]]=0;
                        p2[o2][++tot2[o2]]=(struct case1){px1,py1};
                        link2[o2][tot2[o2]]=flag=1;
                     }
                     else
                     {
                        p2[o2][++tot2[o2]]=(struct case1){px1,py1};
                        link2[o2][tot2[o2]]=flag=0;
                        p2[cur][++tot2[cur]]=(struct case1){px1,py1};
                        link2[cur][tot2[cur]]=1;
                     }
               }
            }
            else if (cj(p[j][k].x-x1,p[j][k].y-y1,x2-x1,y2-y1)*cj(p[j][k+1].x-x1,p[j][k+1].y-y1,x2-x1,y2-y1)<eps&&!zero(cj(p[j][k+1].x-x1,p[j][k+1].y-y1,x2-x1,y2-y1)))
            {
               tmp=solve(x1,y1,x2,y2,p[j][k].x,p[j][k].y,p[j][k+1].x,p[j][k+1].y);
               if (!flag)
               {
                  p2[cur][++tot2[cur]]=tmp;
                  tot2[++o2]=link2[cur][tot2[cur]]=0;
                  flag=1;
                  p2[o2][++tot2[o2]]=tmp;
                  link2[o2][tot2[o2]]=0;
               }
               else
               {
                  p2[o2][++tot2[o2]]=tmp;
                  link2[o2][tot2[o2]]=flag=0;
                  p2[cur][++tot2[cur]]=tmp;
                  link2[cur][tot2[cur]]=0;
               }
            }
         }
         if (flag)
         {
            tot2[cur]--;
            for (k=1;k<=tot2[o2];k++)
            {
               p2[cur][++tot2[cur]]=p2[o2][k];
               link2[cur][tot2[cur]]=link2[o2][k];
            }
            o2--;
         }
      }
      o=o2;
      for (j=1;j<=o;j++)
      {
         tot[j]=0;
         for (k=1;k<=tot2[j];k++)
            if (!zero(p2[j][k].x-p2[j][k%tot2[j]+1].x)||!zero(p2[j][k].y-p2[j][k%tot2[j]+1].y))
            {
               link[j][++tot[j]]=link2[j][k];
               p[j][tot[j]]=p2[j][k];
            }
         p[j][tot[j]+1]=p[j][1];
      }
   }
   for (i=1;i<=o;i++)
   {
      for (j=2;j<tot[i];j++)
         area[i]+=cj(p[i][j].x-p[i][1].x,p[i][j].y-p[i][1].y,p[i][j+1].x-p[i][1].x,p[i][j+1].y-p[i][1].y)/2;
      for (j=1;j<=tot[i];j++)
         if (link[i][j])
         {
            x1=atan2(p[i][j+1].y,p[i][j+1].x)-atan2(p[i][j].y,p[i][j].x);
            if (x1<-eps)
               x1+=2*pi;
            area[i]+=x1*r*r/2-cj(p[i][j].x,p[i][j].y,p[i][j+1].x,p[i][j+1].y)/2;
         }
   }
   x1=dfs(0,0);
   printf("%.10lf %.10lf\n",x1,pi*r*r-x1);
   return 0;
}
