#include <stdio.h>
#include <math.h>
#define eps 1e-12
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dj(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))
#define px(x1,y1,x2,y2) zero(cj(x1,y1,x2,y2))
#define dis(x1,y1,x2,y2) sqrt(((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))
#define in(x,y,x1,y1,x2,y2) (zero(cj((x)-(x1),(y)-(y1),(x2)-(x1),(y2)-(y1)))&&dj((x1)-(x),(y1)-(y),(x2)-(x),(y2)-(y))<eps)
#define check(a,b,c,d,e,f,g,h) (cj((a)-(e),(b)-(f),(g)-(e),(h)-(f))*cj((c)-(e),(d)-(f),(g)-(e),(h)-(f))<eps&&cj((e)-(a),(f)-(b),(c)-(a),(d)-(b))*cj((g)-(a),(h)-(b),(c)-(a),(d)-(b))<eps)

struct case1
{
   double x1,y1,x2,y2;
}p[51];
struct case2
{
   double x,y;
}mid[51],rec[6250001];

void qs(int x,int y)
{
   int i=x,j=y;
   struct case2 t=rec[(x+y)>>1];
   if (x>=y)
      return;
   rec[(x+y)>>1]=rec[x];
   while (i<j)
   {
      while (i<j&&(rec[j].x>t.x+eps||zero(rec[j].x-t.x)&&rec[j].y>t.y))
         j--;
      if (i<j)
         rec[i++]=rec[j];
      while (i<j&&(rec[i].x<t.x-eps||zero(rec[i].x-t.x)&&rec[i].y<t.y))
         i++;
      if (i<j)
         rec[j--]=rec[i];
   }
   rec[i]=t;
   qs(x,i-1);
   qs(i+1,y);
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
   int i,j,k,l,n,s2=0;
   struct case1 tmp;
   struct case2 st1,en1,st2,en2,st3,en3,d;
   double d1,d2,s=0,ans=0;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%lf%lf%lf%lf",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
      mid[i]=solve(p[i].x1,p[i].y1,p[i].x2,p[i].y2,0,0,p[i].y2-p[i].y1,p[i].x1-p[i].x2);
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         tmp=(struct case1){-p[i].x1,-p[i].y1,-p[i].x2,-p[i].y2};
         if (px(tmp.x1-tmp.x2,tmp.y1-tmp.y2,p[j].x1-p[j].x2,p[j].y1-p[j].y2))
            if (in(p[j].x1,p[j].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)||in(p[j].x2,p[j].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
               if (dj(p[j].x1-p[j].x2,p[j].y1-p[j].y2,tmp.x2-tmp.x1,tmp.y2-tmp.y1)>eps)
               {
                  st1=(in(p[j].x2,p[j].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[j].x2,-p[j].y2}:(struct case2){-tmp.x1,-tmp.y1});
                  en1=(in(p[j].x1,p[j].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[j].x1,-p[j].y1}:(struct case2){-tmp.x2,-tmp.y2});
               }
               else
               {
                  st1=(in(p[j].x1,p[j].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[j].x1,-p[j].y1}:(struct case2){-tmp.x1,-tmp.y1});
                  en1=(in(p[j].x2,p[j].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[j].x2,-p[j].y2}:(struct case2){-tmp.x2,-tmp.y2});
               }
            else if (in(tmp.x1,tmp.y1,p[j].x1,p[j].y1,p[j].x2,p[j].y2)&&in(tmp.x2,tmp.y2,p[j].x1,p[j].y1,p[j].x2,p[j].y2))
            {
               st1=(struct case2){p[i].x1,p[i].y1};
               en1=(struct case2){p[i].x2,p[i].y2};
            }
            else
               continue;
         else if (check(p[j].x1,p[j].y1,p[j].x2,p[j].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
         {
            d=solve(tmp.x1,tmp.y1,tmp.x2,tmp.y2,p[j].x1,p[j].y1,p[j].x2,p[j].y2);
            st1=en1=(struct case2){-d.x,-d.y};
         }
         else
            continue;
         for (k=1;k<=n;k++)
         {
            tmp=(struct case1){st1.y,-st1.x,en1.y,-en1.x};
            if (px(tmp.x1-tmp.x2,tmp.y1-tmp.y2,p[k].x1-p[k].x2,p[k].y1-p[k].y2))
               if (in(p[k].x1,p[k].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)||in(p[k].x2,p[k].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
                  if (dj(p[k].x1-p[k].x2,p[k].y1-p[k].y2,tmp.x2-tmp.x1,tmp.y2-tmp.y1)>eps)
                  {
                     st2=(in(p[k].x2,p[k].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[k].y2,p[k].x2}:(struct case2){-tmp.y1,tmp.x1});
                     en2=(in(p[k].x1,p[k].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[k].y1,p[k].x1}:(struct case2){-tmp.y2,tmp.x2});
                  }
                  else
                  {
                     st2=(in(p[k].x1,p[k].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[k].y1,p[k].x1}:(struct case2){-tmp.y1,tmp.x1});
                     en2=(in(p[k].x2,p[k].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){-p[k].y2,p[k].x2}:(struct case2){-tmp.y2,tmp.x2});
                  }
               else if (in(tmp.x1,tmp.y1,p[k].x1,p[k].y1,p[k].x2,p[k].y2)&&in(tmp.x2,tmp.y2,p[k].x1,p[k].y1,p[k].x2,p[k].y2))
               {
                  st2=st1;
                  en2=en1;
               }
               else
                  continue;
            else if (check(p[k].x1,p[k].y1,p[k].x2,p[k].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
            {
               d=solve(tmp.x1,tmp.y1,tmp.x2,tmp.y2,p[k].x1,p[k].y1,p[k].x2,p[k].y2);
               st2=en2=(struct case2){-d.y,d.x};
            }
            else
               continue;
            for (l=1;l<=n;l++)
            {
               tmp=(struct case1){-st2.y,st2.x,-en2.y,en2.x};
               if (px(tmp.x1-tmp.x2,tmp.y1-tmp.y2,p[l].x1-p[l].x2,p[l].y1-p[l].y2))
                  if (in(p[l].x1,p[l].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)||in(p[l].x2,p[l].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
                     if (dj(p[l].x1-p[l].x2,p[l].y1-p[l].y2,tmp.x2-tmp.x1,tmp.y2-tmp.y1)>eps)
                     {
                        st3=(in(p[l].x2,p[l].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){p[l].y2,-p[l].x2}:(struct case2){tmp.y1,-tmp.x1});
                        en3=(in(p[l].x1,p[l].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){p[l].y1,-p[l].x1}:(struct case2){tmp.y2,-tmp.x2});
                     }
                     else
                     {
                        st3=(in(p[l].x1,p[l].y1,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){p[l].y1,-p[l].x1}:(struct case2){tmp.y1,-tmp.x1});
                        en3=(in(p[l].x2,p[l].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2)?(struct case2){p[l].y2,-p[l].x2}:(struct case2){tmp.y2,-tmp.x2});
                     }
                  else if (in(tmp.x1,tmp.y1,p[l].x1,p[l].y1,p[l].x2,p[l].y2)&&in(tmp.x2,tmp.y2,p[l].x1,p[l].y1,p[l].x2,p[l].y2))
                  {
                     st3=st2;
                     en3=en2;
                  }
                  else
                     continue;
               else if (check(p[l].x1,p[l].y1,p[l].x2,p[l].y2,tmp.x1,tmp.y1,tmp.x2,tmp.y2))
               {
                  d=solve(tmp.x1,tmp.y1,tmp.x2,tmp.y2,p[l].x1,p[l].y1,p[l].x2,p[l].y2);
                  st3=en3=(struct case2){d.y,-d.x};
               }
               else
                  continue;
               if (zero(st3.x-en3.x)&&zero(st3.y-en3.y))
                  rec[++s2]=st3;
               else
               {
                  d1=dis(st3.x,st3.y,mid[i].x,mid[i].y);
                  d2=dis(en3.x,en3.y,mid[i].x,mid[i].y)*(1-2*in(mid[i].x,mid[i].y,st3.x,st3.y,en3.x,en3.y));
                  s+=abb(d1-d2);
                  ans+=2*(abb(d1*d1*d1-d2*d2*d2)/3+(mid[i].x*mid[i].x+mid[i].y*mid[i].y)*abb(d1-d2));
               }
            }
         }
      }
   if (s>eps)
      printf("%.10lf\n",ans/s);
   else
   {
      qs(1,s2);
      for (i=1;i<=s2;i++)
         if (i==1||!zero(rec[i].x-rec[i-1].x)||!zero(rec[i].y-rec[i-1].y))
         {
            s++;
            ans+=2*(rec[i].x*rec[i].x+rec[i].y*rec[i].y);
         }
      printf("%.10lf\n",ans/s);
   }
   return 0;
}
