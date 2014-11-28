#include <stdio.h>

struct case1
{
   long u,d,l,r,x,y;
}p[20101]={0,0,0,0,0,0};
struct case2
{
   long t,x,y,s;
}pos[1001]={0,0,0,0};
long hash[27]={0},step[4][2]={{1,0},{0,1},{-1,0},{0,-1}},ans[101]={0},sum[101]={0},l[6]={0};
char bag[101]={0},map[25][25]={0};
long s,fuck=0;

void rem(long x)
{
   long i,j;
   p[p[x].l].r=p[x].r;
   p[p[x].r].l=p[x].l;
   for (i=p[x].d;i!=x;i=p[i].d)
      for (j=p[i].r;j!=i;j=p[j].r)
      {
         sum[p[j].y]--;
         p[p[j].u].d=p[j].d;
         p[p[j].d].u=p[j].u;
      }
}

void res(long x)
{
   long i,j;
   p[p[x].l].r=p[p[x].r].l=x;
   for (i=p[x].d;i!=x;i=p[i].d)
      for (j=p[i].r;j!=i;j=p[j].r)
      {
         sum[p[j].y]++;
         p[p[j].u].d=p[p[j].d].u=j;
      }
}

long dfs(long now)
{
   long i,j,t=0;
   if (!p[0].r)
   {
      s=now-1;
      return 1;
   }
   fuck++;
   if (fuck>=50000)
      return 0;
   for (i=p[0].r;i;i=p[i].r)
      if (!sum[i])
         return 0;
      else if (!t||sum[i]<sum[t])
         t=i;
   rem(t);
   for (i=p[t].d;i!=t;i=p[i].d)
   {
      ans[now]=p[i].x;
      for (j=p[i].r;j!=i;j=p[j].r)
         rem(p[j].y);
      if (dfs(now+1))
         return 1;
      for (j=p[i].r;j!=i;j=p[j].r)
         res(p[j].y);
   }
   res(t);
   return 0;
}

int main()
{
   long i,j,k,a,n,m,x,tot,px,py,tl=0,flag=0;
   scanf("%ld%ld%ld",&n,&m,&x);
   bag[0]=1;
   for (i=1;i<=x;i++)
   {
      scanf("%ld",&l[i]);
      for (j=l[i];j<=n*m;j++)
         bag[j]|=bag[j-l[i]];
   }
   if (!bag[n*m])
      goto loop;
   p[0].l=tot=n*m;
   p[0].r=1;
   for (i=1;i<=n*m;i++)
      p[i]=(struct case1){i,i,i-1,(i+1)%(n*m+1),i};
   for (i=1;i<=x;i++)
   {
      for (j=1;j<=x&&(i==j||l[i]%l[j]);j++);
      if (j<=x)
      {
         for (j=i;j<x;j++)
            l[j]=l[j+1];
         x--;
         i--;
      }
   }
   for (i=1;i<=x;i++)
   {
      for (j=1;j<=n;j++)
         for (k=1;k+l[i]-1<=m;k++)
         {
            pos[++tl]=(struct case2){i,j,k,0};
            tot++;
            p[tot]=(struct case1){p[(j-1)*m+k].u,(j-1)*m+k,tot,tot,tl,(j-1)*m+k};
            p[p[tot].u].d=p[p[tot].d].u=tot;
            sum[p[tot].y]++;
            for (a=1;a<l[i];a++)
            {
               tot++;
               p[tot]=(struct case1){p[(j-1)*m+k+a].u,(j-1)*m+k+a,tot-1,p[tot-1].r,tl,(j-1)*m+k+a};
               p[p[tot].u].d=p[p[tot].d].u=p[p[tot].r].l=p[p[tot].l].r=tot;
               sum[p[tot].y]++;
            }
         }
      if (l[i]>1)
         for (j=1;j<=m;j++)
            for (k=1;k+l[i]-1<=n;k++)
            {
               pos[++tl]=(struct case2){i,k,j,1};
               tot++;
               p[tot]=(struct case1){p[(k-1)*m+j].u,(k-1)*m+j,tot,tot,tl,(k-1)*m+j};
               p[p[tot].u].d=p[p[tot].d].u=tot;
               sum[p[tot].y]++;
               for (a=1;a<l[i];a++)
               {
                  tot++;
                  p[tot]=(struct case1){p[(k+a-1)*m+j].u,(k+a-1)*m+j,tot-1,p[tot-1].r,tl,(k+a-1)*m+j};
                  p[p[tot].u].d=p[p[tot].d].u=p[p[tot].r].l=p[p[tot].l].r=tot;
                  sum[p[tot].y]++;
               }
            }
   }
   if (!dfs(1))
   {
      loop:
      puts("NO");
   }
   else
   {
      puts("YES");
      for (i=1;i<=s;i++)
      {
         flag++;
         if (!pos[ans[i]].s)
         {
            for (j=pos[ans[i]].y;j<=pos[ans[i]].y+l[pos[ans[i]].t]-1;j++)
               for (k=0;k<4;k++)
               {
                  px=pos[ans[i]].x+step[k][0];
                  py=j+step[k][1];
                  if (map[px][py])
                     hash[map[px][py]-'a']=flag;
               }
            for (k=0;hash[k]==flag;k++);
            for (j=pos[ans[i]].y;j<=pos[ans[i]].y+l[pos[ans[i]].t]-1;j++)
               map[pos[ans[i]].x][j]='a'+k;
         }
         else
         {
            for (j=pos[ans[i]].x;j<=pos[ans[i]].x+l[pos[ans[i]].t]-1;j++)
               for (k=0;k<4;k++)
               {
                  px=j+step[k][0];
                  py=pos[ans[i]].y+step[k][1];
                  if (map[px][py])
                     hash[map[px][py]-'a']=flag;
               }
            for (k=0;hash[k]==flag;k++);
            for (j=pos[ans[i]].x;j<=pos[ans[i]].x+l[pos[ans[i]].t]-1;j++)
               map[j][pos[ans[i]].y]='a'+k;
         }
      }
      for (i=1;i<=n;i++)
         puts(map[i]+1);
   }
   return 0;
}
