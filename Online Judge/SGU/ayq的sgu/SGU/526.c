#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))

struct case1
{
   long long st,en;
}rec[3002][3002],tmp[3002];
struct case2
{
   int l,r,t;
}st[3002];
struct case3
{
   long long pos;
   double t;
}ans[3002];
int tot[3002];

int main()
{
   int i,j,k,v,n,o,x=0;
   long long g;
   struct case2 t;
   scanf("%d%I64d%d",&v,&g,&n);
   for (i=1;i<=n;i++)
      scanf("%d%d%d",&st[i].l,&st[i].r,&st[i].t);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (st[i].t>st[j].t)
         {
            t=st[i];
            st[i]=st[j];
            st[j]=t;
         }
   st[++n].t=1000000;
   tot[0]=1;
   for (i=1;i<=n;i++)
   {
      for (j=1;j<=tot[i-1];j=k+1)
      {
         k=j;
         while (k<tot[i-1]&&rec[i-1][k+1].st-2LL*v*(st[i].t-st[i-1].t)<=rec[i-1][k].en)
            k++;
         rec[i][++tot[i]]=(struct case1){rec[i-1][j].st-1LL*v*(st[i].t-st[i-1].t),rec[i-1][k].en+1LL*v*(st[i].t-st[i-1].t)};
      }
      o=0;
      for (j=1;j<=tot[i];j++)
      {
         if (rec[i][j].st<=g&&rec[i][j].en>=g)
         {
            k=-1000000;
            for (j=1;j<=tot[i-1];j++)
            {
               if (abb(rec[i-1][j].st-g)<abb(k-g))
                  k=rec[i-1][j].st;
               if (abb(rec[i-1][j].en-g)<abb(k-g))
                  k=rec[i-1][j].en;
            }
            ans[o=1]=(struct case3){g,st[i-1].t+1.0*abb(k-g)/v};
            g=k;
            while (i--)
            {
               ans[++o]=(struct case3){g,st[i].t};
               for (j=1;j<=tot[i-1]&&(rec[i-1][j].en<g-1LL*v*(st[i].t-st[i-1].t)||rec[i-1][j].st>g+1LL*v*(st[i].t-st[i-1].t));j++);
               g=min(g+1LL*v*(st[i].t-st[i-1].t),rec[i-1][j].en);
            }
            for (i=o;i>=2;i--)
               x+=(ans[i-1].t>ans[i].t+1e-8);
            printf("%d\n",x);
            for (i=o;i>=2;i--)
               if (ans[i-1].t>ans[i].t+1e-8)
                  printf("%.15lf %.15lf\n",(ans[i-1].pos-ans[i].pos)/(ans[i-1].t-ans[i].t),ans[i-1].t-ans[i].t);
            goto end;
         }
         if (rec[i][j].en<=st[i].l||rec[i][j].st>=st[i].r)
            tmp[++o]=rec[i][j];
         else
         {
            if (rec[i][j].st<=st[i].l)
               tmp[++o]=(struct case1){rec[i][j].st,st[i].l};
            if (rec[i][j].en>=st[i].r)
               tmp[++o]=(struct case1){st[i].r,rec[i][j].en};
         }
      }
      if (!(tot[i]=o))
      {
         puts("-1");
         goto end;
      }
      for (j=1;j<=o;j++)
         rec[i][j]=tmp[j];
   }
   end:
   return 0;
}
