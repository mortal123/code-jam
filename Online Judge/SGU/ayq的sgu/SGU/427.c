#include <stdio.h>
#define eps 1e-8
#define zero(a) (abb(a)<eps)
#define abb(a) ((a)>0?(a):(-(a)))

struct case1
{
   double x,y,z;
}p[101];
int rec[101],head[101],du[101],e[1001],next[1001];
char hash[101];
int o=0,totm=0,flag=0;

void add(int a,int b)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
   du[a]++;
   du[b]++;
}

int find(double x,double y,double z)
{
   int i;
   for (i=1;i<=o;i++)
      if (zero(p[i].x-x)&&zero(p[i].y-y)&&zero(p[i].z-z))
         return i;
   p[++o]=(struct case1){x,y,z};
   return o;
}

void dfs(int now,int tot)
{
   int i,j;
   int tmp[101];
   hash[now]=1;
   rec[tot]=now;
   if (tot==o)
   {
      for (i=head[now];i;i=next[i])
         if (e[i]==1)
            flag=1;
   }
   else
   {
      tmp[0]=0;
      for (i=head[now];i;i=next[i])
         if (!hash[e[i]])
            du[tmp[++tmp[0]]=e[i]]--;
      for (i=1;i<tmp[0];i++)
         for (j=i+1;j<=tmp[0];j++)
            if (du[tmp[i]]>du[tmp[j]])
            {
               tmp[i]^=tmp[j];
               tmp[j]^=tmp[i];
               tmp[i]^=tmp[j];
            }
      for (i=1;i<=tmp[0];i++)
         if (!hash[tmp[i]])
         {
            dfs(tmp[i],tot+1);
            if (flag)
               return;
         }
      for (i=head[now];i;i=next[i])
         if (!hash[e[i]])
            du[e[i]]++;
   }
   hash[now]=0;
}

int main()
{
   int i,j,n,m;
   double x,y,z,lx,ly,lz,tx,ty,tz;
   scanf("%d",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%d%lf%lf%lf",&m,&x,&y,&z);
      lx=tx=x;
      ly=ty=y;
      lz=tz=z;
      for (j=2;j<=m;j++)
      {
         scanf("%lf%lf%lf",&x,&y,&z);
         add(find(x,y,z),find(lx,ly,lz));
         lx=x;
         ly=y;
         lz=z;
      }
      add(find(x,y,z),find(tx,ty,tz));
   }
   dfs(1,1);
   printf("Yes\n%d\n",o);
   for (i=1;i<=o;i++)
      printf("%.9lf %.9lf %.9lf\n",p[rec[i]].x,p[rec[i]].y,p[rec[i]].z);
   return 0;
}
