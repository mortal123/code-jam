#include <stdio.h>
#include <math.h>
#define eps 1e-7
#define zero(a) (abb(a)<=eps)
#define abb(a) ((a)>0?(a):(-(a)))
#define max(a,b) ((a)>(b)?(a):(b))
#define dis(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))
#define cj(a,b,c) ((p[b].x-p[a].x)*(p[c].y-p[a].y)-(p[c].x-p[a].x)*(p[b].y-p[a].y))
#define dj(a,b,c) ((p[b].x-p[a].x)*(p[c].x-p[a].x)+(p[b].y-p[a].y)*(p[c].y-p[a].y))

struct case1
{
   int x,y,pos;
}p[100001];
struct case2
{
   int a,b,v;
}rec[2000001];
struct case3
{
   double x,y;
};
struct case4
{
   double x1,y1,x2,y2;
};
int q[100001],pos[100001],h[100001],st[100001][17],max[100001][17],head[100001],v[200001],f[100001],next[4100001],e[4100001],last[4100001];
int n,totm;

void add(int a,int b)
{
   e[++totm]=b;
   last[totm]=a;
   next[totm]=next[a];
   next[a]=last[next[a]]=totm;
}

void add2(int a,int b,int c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

int getf(int now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

void qs(int x,int y)
{
   int i=x,j=y;
   struct case1 t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while (i<j&&(p[j].x>t.x||p[j].x==t.x&&p[j].y>t.y))
         j--;
      if (i<j)
         p[i++]=p[j];
      while (i<j&&(p[i].x<t.x||p[i].x==t.x&&p[i].y<t.y))
         i++;
      if (i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

void qs2(int x,int y)
{
   int i=x,j=y;
   struct case2 t=rec[(x+y)>>1];
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
   qs2(x,i-1);
   qs2(i+1,y);
}

void dfs(int now,int last,int d)
{
   int i;
   h[now]=d;
   for (i=1;st[now][i-1];i++)
   {
      st[now][i]=st[st[now][i-1]][i-1];
      max[now][i]=max(max[now][i-1],max[st[now][i-1]][i-1]);
   }
   for (i=head[now];i;i=next[i])
      if (e[i]!=last)
      {
         st[e[i]][0]=now;
         max[e[i]][0]=v[i];
         dfs(e[i],now,d+1);
      }
}

struct case4 solve1(int a,int b)
{
   struct case4 tmp;
   tmp.x1=(p[a].x+p[b].x)/2.0;
   tmp.y1=(p[a].y+p[b].y)/2.0;
   tmp.x2=tmp.x1+p[b].y-p[a].y;
   tmp.y2=tmp.y1+p[a].x-p[b].x;
   return tmp;
}

struct case3 solve2(double a,double b,double c,double d,double e,double f,double g,double h)
{
   struct case3 t;
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

struct case3 get(int a,int b,int c)
{
   struct case4 p1=solve1(a,b),p2=solve1(a,c);
   return solve2(p1.x1,p1.y1,p1.x2,p1.y2,p2.x1,p2.y1,p2.x2,p2.y2);
}

void del(int a,int b,int c)
{
   int i;
   for (i=next[a];i;i=next[i])
      if ((long long)cj(a,b,e[i])*cj(a,c,e[i])<0&&(long long)cj(b,a,c)*cj(b,e[i],c)<0)
      {
         last[next[i]]=last[i];
         next[last[i]]=next[i];
         last[next[i^1]]=last[i^1];
         next[last[i^1]]=next[i^1];
      }
}

void build(int st,int en)
{
   int i,pl,pr,tmp,flag,mid=(st+en)>>1,top=1;
   struct case3 c,minc;
   if (st==en-1)
   {
      add(st,en);
      add(en,st);
   }
   if (st<en-1)
   {
      build(st,mid);
      build(mid+1,en);
      q[1]=en;
      for (i=en-1;i>st;i--)
         if (cj(q[top],st,i)>=0)
         {
            while (top>1&&cj(q[top-1],q[top],i)>0)
               top--;
            q[++top]=i;
         }
      q[++top]=st;
      for (i=1;q[i]>mid;i++);
      pl=q[i];
      pr=q[i-1];
      while (1)
      {
         minc=(struct case3){-1e100,1e100};
         flag=0;
         for (i=next[pl];i;i=next[i])
            if (cj(pl,pr,e[i])>0)
            {
               c=get(pl,pr,e[i]);
               if (p[pl].x<p[pr].x&&c.y<minc.y||p[pl].x==p[pr].x&&c.x>minc.x)
               {
                  minc=c;
                  tmp=e[i];
                  flag=1;
               }
            }
            else if (cj(pl,pr,e[i])==0&&dj(pl,pr,e[i])>0)
            {
               minc=(struct case3){1e100,-1e100};
               tmp=e[i];
               flag=1;
            }
         for (i=next[pr];i;i=next[i])
            if (cj(pr,pl,e[i])<0)
            {
               c=get(pr,pl,e[i]);
               if (p[pl].x<p[pr].x&&c.y<minc.y||p[pl].x==p[pr].x&&c.x>minc.x)
               {
                  minc=c;
                  tmp=e[i];
                  flag=2;
               }
            }
            else if (cj(pr,pl,e[i])==0&&dj(pr,pl,e[i])>0)
            {
               minc=(struct case3){1e100,-1e100};
               tmp=e[i];
               flag=2;
            }
         add(pl,pr);
         add(pr,pl);
         if (flag==1)
         {
            del(pl,tmp,pr);
            pl=tmp;
         }
         else if (flag==2)
         {
            del(pr,tmp,pl);
            pr=tmp;
         }
         else
            break;
      }
   }
}

int main()
{
   int i,j,n,a,b,ans,o=0;
   scanf("%d",&n);
   totm=n+!(n&1);
   for (i=1;i<=n;i++)
   {
      f[i]=p[i].pos=i;
      scanf("%d%d",&p[i].x,&p[i].y);
   }
   qs(1,n);
   for (i=1;i<=n;i++)
      pos[p[i].pos]=i;
   build(1,n);
   for (i=1;i<n;i++)
      for (j=next[i];j;j=next[j])
         if (e[j]>i)
            rec[++o]=(struct case2){i,e[j],dis(p[i].x,p[i].y,p[e[j]].x,p[e[j]].y)};
   totm=0;
   qs2(1,o);
   for (i=1;i<=o;i++)
      if ((a=getf(rec[i].a))!=(b=getf(rec[i].b)))
      {
         f[b]=a;
         add2(rec[i].a,rec[i].b,rec[i].v);
         add2(rec[i].b,rec[i].a,rec[i].v);
      }
   dfs(1,0,0);
   scanf("%d",&n);
   while (n--)
   {
      scanf("%d%d",&a,&b);
      if (a==b)
      {
         puts("0");
         continue;
      }
      a=pos[a];
      b=pos[b];
      ans=0;
      for (j=16;j>=0;j--)
         if (h[a]-(1<<j)>=h[b])
         {
            ans=max(ans,max[a][j]);
            a=st[a][j];
         }
      for (j=16;j>=0;j--)
         if (h[b]-(1<<j)>=h[a])
         {
            ans=max(ans,max[b][j]);
            b=st[b][j];
         }
      for (j=16;j>=0;j--)
         if (st[a][j]&&st[a][j]!=st[b][j])
         {
            ans=max(ans,max[a][j]);
            ans=max(ans,max[b][j]);
            a=st[a][j];
            b=st[b][j];
         }
      if (a!=b)
      {
         ans=max(ans,max[a][0]);
         ans=max(ans,max[b][0]);
      }
      printf("%.10lf\n",sqrt(ans));
   }
   return 0;
}
