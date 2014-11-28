#include <stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define cj(x1,y1,x2,y2) ((long long)(x1)*(y2)-(long long)(x2)*(y1))

struct case1
{
   int x,y1,y2;
}l[4][100001];
struct case2
{
   int st,en,s,f1,f2;
}p[100001];
int tot[4];
int n;

void qs(int x,int y,int v)
{
   int i=x,j=y;
   struct case1 t=l[v][(x+y)>>1];
   if (x>=y)
      return;
   l[v][(x+y)>>1]=l[v][x];
   while (i<j)
   {
      while (i<j&&l[v][j].x>t.x)
         j--;
      if (i<j)
         l[v][i++]=l[v][j];
      while (i<j&&l[v][i].x<t.x)
         i++;
      if (i<j)
         l[v][j--]=l[v][i];
   }
   l[v][i]=t;
   qs(x,i-1,v);
   qs(i+1,y,v);
}

int save(int x1,int y1,int x2,int y2)
{
   if (x1==x2)
      l[0][++tot[0]]=(struct case1){x1,min(y1,y2),max(y1,y2)};
   else if (y1==y2)
      l[1][++tot[1]]=(struct case1){y1,min(x1,x2),max(x1,x2)};
   else if (abb(x2-x1)!=abb(y2-y1))
      return 0;
   else if ((min(x1,x2)==x1)^(min(y1,y2)==y1))
      l[2][++tot[2]]=(struct case1){x1+y1,min(x1,x2),max(x1,x2)};
   else
      l[3][++tot[3]]=(struct case1){x1-y1,min(x1,x2),max(x1,x2)};
   return 1;
}

void build(int now,int st,int en)
{
   int mid=(st+en)>>1;
   p[now].st=st;
   p[now].en=en;
   if (st<en-1)
   {
      build(now<<1,st,mid);
      build((now<<1)+1,mid,en);
   }
}

void ins(int now,int st,int en)
{
   int mid=(p[now].st+p[now].en)>>1;
   if (p[now].st==st&&p[now].en==en)
   {
      p[now].f2^=1;
      p[now].s=en-st-p[now].s;
   }
   else
   {
      if (p[now].f1)
      {
         p[now<<1].f2=p[now<<1].s=p[(now<<1)+1].f2=p[(now<<1)+1].s=p[now].f1=0;
         p[now<<1].f1=p[(now<<1)+1].f1=1;
      }
      if (p[now].f2)
      {
         p[now<<1].f2^=1;
         p[(now<<1)+1].f2^=1;
         p[now<<1].s=mid-p[now].st-p[now<<1].s;
         p[(now<<1)+1].s=p[now].en-mid-p[(now<<1)+1].s;
         p[now].f2=0;
      }
      if (en<=mid)
         ins(now<<1,st,en);
      else if (st>=mid)
         ins((now<<1)+1,st,en);
      else
      {
         ins(now<<1,st,mid);
         ins((now<<1)+1,mid,en);
      }
      p[now].s=p[now<<1].s+p[(now<<1)+1].s;
   }
}

int main()
{
   int i,j,k,a,q,m,x1,y1,x2,y2,x3,y3,flag;
   long long s;
   build(1,0,25000);
   scanf("%d",&q);
   while (q--)
   {
      scanf("%d%d",&n,&m);
      s=tot[0]=tot[1]=tot[2]=tot[3]=0;
      flag=1;
      for (i=1;i<=m;i++)
      {
         scanf("%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
         flag&=((x1==x2)+(x2==x3)+(x3==x1)+(y1==y2)+(y2==y3)+(y3==y1)==2);
         s+=abb(cj(x2-x1,y2-y1,x3-x1,y3-y1));
         flag&=save(x1,y1,x2,y2);
         flag&=save(x2,y2,x3,y3);
         flag&=save(x3,y3,x1,y1);
      }
      if (!flag||s!=(long long)n*n)
         puts("NO");
      else
      {
         save(0,0,0,n);
         save(0,0,n,0);
         save(0,n,n,0);
         for (i=0;i<4;i++)
         {
            qs(1,tot[i],i);
            for (j=1;j<=tot[i];j=k+1)
            {
               k=j;
               while (k<tot[i]&&l[i][k+1].x==l[i][j].x)
                  k++;
               p[1].f1=1;
               p[1].s=p[1].f2=0;
               for (a=j;a<=k;a++)
                  ins(1,l[i][a].y1,l[i][a].y2);
               if (p[1].s)
               {
                  puts("NO");
                  goto end;
               }
            }
         }
         puts("YES");
         end:;
      }
   }
   return 0;
}
