#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   int c,s,p,t;
}rec[10001];
int s[101][101],c[101],tot[101][101],next1[101][101],next2[101][102];
int n,st=1,en=0,last=0;

int check_in(int t,int p,int e)
{
   int i,j,tc,ts,m1=-1,m2,sl,sr;
   for (i=1;i<=n;i++)
      for (j=1;j+p-1<=c[i];j++)
         if (!(tot[i][j+p-1]-tot[i][j-1]))
         {
            sl=min(j-next1[i][j]-1,oo-10000);
            sr=min(next2[i][j+p-1]-j-p,oo-10000);
            if (min(sl,sr)>m1||min(sl,sr)==m1&&max(sl,sr)>m2)
            {
               m1=min(sl,sr);
               m2=max(sl,sr);
               tc=i;
               ts=j;
            }
         }
   if (m1==-1)
      return 0;
   for (i=en;i>=st&&rec[i].t>t+e;i--)
      rec[i+1]=rec[i];
   rec[i+1]=(struct case1){tc,ts,p,t+e};
   en++;
   for (i=ts;i<=ts+p-1;i++)
      s[tc][i]=1;
   for (i=1;i<=c[tc];i++)
   {
      tot[tc][i]=tot[tc][i-1]+s[tc][i];
      next1[tc][i]=s[tc][i]?i:next1[tc][i-1];
   }
   for (i=c[tc];i>=1;i--)
      next2[tc][i]=s[tc][i]?i:next2[tc][i+1];
   return 1;
}

void check_out()
{
   int i;
   for (i=rec[st].s;i<=rec[st].s+rec[st].p-1;i++)
      s[rec[st].c][i]=0;
   for (i=1;i<=c[rec[st].c];i++)
   {
      tot[rec[st].c][i]=tot[rec[st].c][i-1]+s[rec[st].c][i];
      next1[rec[st].c][i]=s[rec[st].c][i]?i:next1[rec[st].c][i-1];
   }
   for (i=c[rec[st].c];i>=1;i--)
      next2[rec[st].c][i]=s[rec[st].c][i]?i:next2[rec[st].c][i+1];
   st++;
}

int main()
{
   int i,j,m,q,t,p,w,e,f,tnow,totp=0;
   double ans=0;
   scanf("%d%d%d",&n,&m,&q);
   for (i=1;i<=n;i++)
   {
      scanf("%d",&c[i]);
      for (j=0;j<=c[i];j++)
      {
         next1[i][j]=-oo;
         next2[i][j+1]=oo;
      }
   }
   for (i=1;i<=m;i++)
   {
      scanf("%d%d%d%d",&t,&p,&w,&e);
      totp+=p;
      tnow=max(last,t);
      f=0;
      while (st<=en&&rec[st].t<=tnow)
         check_out();
      if (tnow<=min(q-1,t+w))
         while (!(f=check_in(tnow,p,e))&&st<=en&&rec[st].t<=min(q-1,t+w))
         {
            tnow=rec[st].t;
            while (st<=en&&rec[st].t==tnow)
               check_out();
         }
      if (!f)
      {
         ans-=p;
         last=max(last,t+w);
      }
      else
      {
         ans+=1.0*p*(w-tnow+t)/w;
         last=max(last,tnow);
      }
   }
   printf("%.16lf\n",ans/totp);
   return 0;
}
