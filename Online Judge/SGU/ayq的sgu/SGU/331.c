#include <stdio.h>
#include <math.h>
#define eps 1e-12
#define oo 1000000000
#define pi 3.1415926535897932384626433832795
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))

struct case1
{
   double v;
   int pos;
}rec[200001];
struct case2
{
   int x1,y1,x2,y2;
}p[100001];
double s[200001],a[6],b[6],x[6],f[200001][6];
int last[200001][6][2],d[200001][2];
double c;
int o=0;

void qs1(int x,int y)
{
   int i=x,j=y;
   struct case1 t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&rec[j].v>t.v)
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&rec[i].v<t.v)
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs1(x,i-1);
   qs1(i+1,y);
}

void qs2(int x,int y)
{
   int i=x,j=y;
   struct case2 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&p[j].x1>t.x1)
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&p[i].x1<t.x1)
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs2(x,i-1);
   qs2(i+1,y);
}

void ins(double x1,int y1,double x2,int y2)
{
   o++;
   rec[o]=(struct case1){x1,o};
   p[(++o)/2]=(struct case2){0,y1,0,y2};
   rec[o]=(struct case1){x2,o};
}

void ins2(int i,int j,double t)
{
   int k;
   double X;
   if (zero(t-1))
      X=pi/2;
   else if (zero(t+1))
      X=-pi/2;
   else if (abb(t)<1)
      X=asin(t);
   else
      return;
   for (k=-5;k<=200;k++)
   {
      if (X+k*2*pi-x[i]>=0)
         ins(X+k*2*pi-x[i],i,X+k*2*pi+abb(j-i)*c-x[i],j);
      if (-X+(k*2+1)*pi-x[i]>=0)
         ins(-X+(k*2+1)*pi-x[i],i,-X+(k*2+1)*pi+abb(j-i)*c-x[i],j);
   }
}

int main()
{
   int i,j,k=1,q,n,px,py,o2=0;
   double l,r,X,A,B,C,t1,t2,alf,bet,drt,mid,v,ans=oo;
   scanf("%d%lf%lf",&n,&v,&c);
   for (i=1;i<=n;i++)
   {
      if (i>1)
         ins(0,1,(i-1)*c,i);
      scanf("%lf%lf%lf",&a[i],&b[i],&x[i]);
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (i!=j)
            if (zero(a[j]))
            {
               if (!zero(a[i]))
                  ins2(i,j,(b[j]-b[i])/a[i]);
            }
            else
            {
               alf=sin(x[j]-x[i]+abb(j-i)*c);
               bet=cos(x[j]-x[i]+abb(j-i)*c);
               if (zero(alf))
               {
                  if (!zero(a[i]-a[j]*bet))
                     ins2(i,j,(b[j]-b[i])/(a[i]-a[j]*bet));
               }
               else
               {
                  t1=(a[i]/a[j]-bet)/alf;
                  t2=(b[i]-b[j])/a[j]/alf;
                  A=t1*t1+1;
                  B=2*t1*t2;
                  C=t2*t2-1;
                  drt=B*B-4*A*C;
                  if (zero(drt))
                     ins2(i,j,-B/2/A);
                  else if (drt>0)
                  {
                     ins2(i,j,(-B+sqrt(drt))/2/A);
                     ins2(i,j,(-B-sqrt(drt))/2/A);
                  }
               }
            }
   qs1(1,o);
   for (i=1;i<=o;i++)
   {
      if (i==1||!zero(rec[i].v-rec[i-1].v))
         s[++o2]=rec[i].v;
      if (rec[i].pos&1)
         p[rec[i].pos/2+1].x1=o2;
      else
         p[rec[i].pos/2].x2=o2;
   }
   qs2(1,o>>=1);
   s[(o2+=!o2)+1]=10000;
   for (i=1;i<=o2+1;i++)
      for (j=1;j<=n;j++)
         f[i][j]=-oo;
   f[1][1]=0;
   for (i=1;i<=o2;i++)
   {
      for (j=1;j<=n;j++)
      {
         if (f[i][j]<v&&b[j]*s[i+1]-a[j]*cos(s[i+1]+x[j])-b[j]*s[i]+a[j]*cos(s[i]+x[j])+f[i][j]>=v)
         {
            l=s[i];
            r=s[i+1];
            for (q=1;q<=100;q++)
            {
               mid=(l+r)/2;
               if (b[j]*mid-a[j]*cos(mid+x[j])-b[j]*s[i]+a[j]*cos(s[i]+x[j])+f[i][j]>=v)
                  r=mid;
               else
                  l=mid;
            }
            if (r<ans)
            {
               ans=r;
               px=i;
               py=j;
            }
         }
         if (b[j]*s[i+1]-a[j]*cos(s[i+1]+x[j])-b[j]*s[i]+a[j]*cos(s[i]+x[j])+f[i][j]>f[i+1][j])
         {
            f[i+1][j]=b[j]*s[i+1]-a[j]*cos(s[i+1]+x[j])-b[j]*s[i]+a[j]*cos(s[i]+x[j])+f[i][j];
            last[i+1][j][0]=i;
            last[i+1][j][1]=j;
         }
      }
      while (k<=o&&p[k].x1==i)
      {
         if (f[p[k].x1][p[k].y1]>f[p[k].x2][p[k].y2])
         {
            f[p[k].x2][p[k].y2]=f[p[k].x1][p[k].y1];
            last[p[k].x2][p[k].y2][0]=p[k].x1;
            last[p[k].x2][p[k].y2][1]=p[k].y1;
         }
         k++;
      }
   }
   o=0;
   i=px;
   j=py;
   while (i>1)
   {
      if (last[i][j][1]!=j)
      {
         d[++o][0]=last[i][j][0];
         d[o][1]=j;
      }
      py=j;
      j=last[i][j][1];
      i=last[i][py][0];
   }
   printf("%.15lf\n%d\n",ans,o);
   for (i=o;i>=1;i--)
      printf("%d %.15lf\n",d[i][1],s[d[i][0]]);
   return 0;
}
