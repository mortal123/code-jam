#include <stdio.h>
#define oo 1000000000

long a[21]={0},map[21][21]={0},head[10001]={0},e[10001]={0},next[10001]={0},r[10001]={0},dis[10001]={0},gap[10001]={0},last[10001]={0},laste[10001]={0};
long totm=1;

void add(long x,long y,long z)
{
   e[++totm]=y;
   next[totm]=head[x];
   head[x]=totm;
   r[totm]=z;
   e[++totm]=x;
   next[totm]=head[y];
   head[y]=totm;
}

int main()
{
   long i,j,n,t,min,need=0,flow=0,s=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   scanf("%ld",&t);
   a[1]+=t;
   for (i=1;i<n;i++)
      scanf("%ld",&t);
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
      {
         scanf("%ld",&map[i][j]);
         if (j>i&&i>1&&map[i][j])
         {
            s++;
            need+=map[i][j];
         }
      }
   for (i=2;i<=n;i++)
      if (a[1]<a[i])
      {
         printf("NO\n");
         goto end;
      }
   t=1;
   for (i=2;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (map[i][j])
         {
            add(1,++t,map[i][j]);
            add(t,i+s,oo);
            add(t,j+s,oo);
         }
   for (i=1;i<n;i++)
      add(i+s+1,s+n+1,a[1]-a[i+1]);
   n=gap[0]=n+s+1;
   for (i=1;dis[1]<n;)
   {
      for (j=head[i];j;j=next[j])
         if (r[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==n)
      {
         min=oo;
         for (;last[i];i=last[i])
            if (r[laste[i]]<min)
               min=r[laste[i]];
         flow+=min;
         for (i=n;last[i];i=last[i])
         {
            r[laste[i]]-=min;
            r[laste[i]^1]+=min;
         }
      }
      else if (!j)
      {
         if (gap[dis[i]]==1)
            break;
         min=oo;
         for (j=head[i];j;j=next[j])
            if (r[j]&&dis[e[j]]<min)
               min=dis[e[j]];
         min++;
         if (min>n)
            min=n;
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (i!=1)
            i=last[i];
      }
   }
   printf("%s\n",(need==flow)?"YES":"NO");
   end:
   return 0;
}
