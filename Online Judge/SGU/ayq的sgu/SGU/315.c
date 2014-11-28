#include <stdio.h>
#include <math.h>
#define eps 1e-9
#define pi 3.1415926535897932384626433832795
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dj(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))
#define dis(a,b) sqrt((d[a].x-d[b].x)*(d[a].x-d[b].x)+(d[a].y-d[b].y)*(d[a].y-d[b].y))

struct case1
{
   double x1,y1,x2,y2;
}p[51];
struct case2
{
   double x,y,d;
   int pos;
}d[2601];
int hash[5201],pos[2601],head[5201],e[10001],next[10001],tmp[10001][2],rec[101];
double dis[5201],v[10001];
int totm=0,o=0,s=0;

void add(long a,long b,double c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

int find(double x,double y)
{
   int i;
   for (i=1;i<=o;i++)
      if (zero(d[i].x-x)&&zero(d[i].y-y))
         return i;
   o++;
   d[o]=(struct case2){x,y,atan2(y,x),o};
   return o;
}

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

int main()
{
   int i,j,k,n,a,b,tot;
   struct case2 t;
   double ans=0;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf%lf",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
      if (zero(p[i].x1-p[i].x2)&&zero(p[i].y1-p[i].y2))
      {
         i--;
         n--;
      }
   }
   for (i=1;i<=n;i++)
   {
      rec[1]=find(p[i].x1,p[i].y1);
      rec[2]=find(p[i].x2,p[i].y2);
      tot=2;
      for (j=1;j<=n;j++)
         if (i!=j)
            if (zero(cj(p[i].x2-p[i].x1,p[i].y2-p[i].y1,p[j].x2-p[j].x1,p[j].y2-p[j].y1)))
            {
               if (zero(cj(p[j].x1-p[i].x1,p[j].y1-p[i].y1,p[i].x2-p[i].x1,p[i].y2-p[i].y1)))
               {
                  if (dj(p[j].x1-p[i].x1,p[j].y1-p[i].y1,p[i].x2-p[i].x1,p[i].y2-p[i].y1)>eps&&dj(p[j].x1-p[i].x2,p[j].y1-p[i].y2,p[i].x1-p[i].x2,p[i].y1-p[i].y2)>eps&&(!zero(p[j].x1)||!zero(p[j].y1)))
                     rec[++tot]=find(p[j].x1,p[j].y1);
                  if (dj(p[j].x2-p[i].x1,p[j].y2-p[i].y1,p[i].x2-p[i].x1,p[i].y2-p[i].y1)>eps&&dj(p[j].x2-p[i].x2,p[j].y2-p[i].y2,p[i].x1-p[i].x2,p[i].y1-p[i].y2)>eps&&(!zero(p[j].x2)||!zero(p[j].y2)))
                     rec[++tot]=find(p[j].x2,p[j].y2);
               }
            }
            else if (cj(p[i].x1-p[j].x1,p[i].y1-p[j].y1,p[j].x2-p[j].x1,p[j].y2-p[j].y1)*cj(p[i].x2-p[j].x1,p[i].y2-p[j].y1,p[j].x2-p[j].x1,p[j].y2-p[j].y1)<eps&&cj(p[j].x1-p[i].x1,p[j].y1-p[i].y1,p[i].x2-p[i].x1,p[i].y2-p[i].y1)*cj(p[j].x2-p[i].x1,p[j].y2-p[i].y1,p[i].x2-p[i].x1,p[i].y2-p[i].y1)<eps)
            {
               t=solve(p[i].x1,p[i].y1,p[i].x2,p[i].y2,p[j].x1,p[j].y1,p[j].x2,p[j].y2);
               if (!zero(t.x)||!zero(t.y))
                  rec[++tot]=find(t.x,t.y);
            }
      for (j=1;j<tot;j++)
         for (k=j+1;k<=tot;k++)
            if (d[rec[k]].x<d[rec[j]].x-eps||zero(d[rec[j]].x-d[rec[k]].x)&&d[rec[k]].y<d[rec[j]].y)
            {
               rec[j]^=rec[k];
               rec[k]^=rec[j];
               rec[j]^=rec[k];
            }
      for (j=1;j<tot;j++)
         if (!zero(d[rec[j]].d-d[rec[j+1]].d))
         {
            if (d[rec[j]].d<d[rec[j+1]].d)
            {
               a=rec[j];
               b=rec[j+1];
            }
            else
            {
               a=rec[j+1];
               b=rec[j];
            }
            if (d[a].d+pi>d[b].d+eps)
            {
               tmp[++s][0]=a;
               tmp[s][1]=b;
               tmp[++s][0]=a+2600;
               tmp[s][1]=b+2600;
            }
            else if (d[a].d+pi<d[b].d-eps)
            {
               tmp[++s][0]=b;
               tmp[s][1]=a+2600;
            }
         }
   }
   for (i=1;i<o;i++)
      for (j=i+1;j<=o;j++)
         if (d[i].d>d[j].d)
         {
            t=d[i];
            d[i]=d[j];
            d[j]=t;
         }
   for (i=1;i<=o;i++)
      pos[d[i].pos]=i;
   for (i=1;i<=s;i++)
   {
      a=((tmp[i][0]<=2600)?pos[tmp[i][0]]:pos[tmp[i][0]-2600]+o);
      b=((tmp[i][1]<=2600)?pos[tmp[i][1]]:pos[tmp[i][1]-2600]+o);
      add(a,b,dis((a-1)%o+1,(b-1)%o+1));
   }
   for (i=1;i<=o;i++)
   {
      hash[i]=i;
      dis[i]=0;
      for (j=i;j<i+o;j++)
         if (hash[j]==i)
            for (k=head[j];k;k=next[k])
               if (e[k]<=i+o)
               {
                  if (hash[e[k]]!=i)
                  {
                     hash[e[k]]=i;
                     dis[e[k]]=0;
                  }
                  dis[e[k]]=max(dis[e[k]],dis[j]+v[k]);
               }
      if (hash[i+o]==i)
         ans=max(ans,dis[i+o]);
   }
   if (zero(ans))
      puts("0");
   else
      printf("%lf\n",ans);
   return 0;
}
