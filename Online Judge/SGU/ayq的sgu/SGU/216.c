#include <stdio.h>

long e[20001]={0},next[20001]={0},head[10001]={0},color[10001]={0},ans[10001]={0},s[10001]={0},que[10001]={0};
char hash[10001]={'\0'};
long b,p=0,totm=0,tot=0;

void add(long x,long y)
{
   e[++totm]=y;
   next[totm]=head[x];
   head[x]=totm;
}

long getsum(long now,long last)
{
   long i;
   s[now]=1;
   for (i=head[now];i;i=next[i])
      if (e[i]!=last)
         s[now]+=getsum(e[i],now);
   return s[now];
}

void paint(long now,long last)
{
   long i;
   hash[now]=1;
   color[now]=tot;
   for (i=head[now];i;i=next[i])
      if (e[i]!=last&&!hash[e[i]])
         paint(e[i],now);
}

void dfs(long now)
{
   long i,t,rec=p,sum=0,flag;
   for (i=head[now];i;i=next[i])
      if (!hash[e[i]]&&s[e[i]]>2*b)
      {
         flag=e[i];
         break;
      }
   for (i=head[now];i&&s[now]>3*b;i=next[i])
      if (!hash[e[i]]&&e[i]!=flag)
      {
         if (s[e[i]]<b)
         {
            que[++p]=e[i];
            sum+=s[e[i]];
            if (sum>=3*b)
            {
               ans[++tot]=now;
               color[now]=tot;
               while (sum-s[que[p]]>=b)
               {
                  sum-=s[que[p]];
                  s[now]-=s[que[p]];
                  paint(que[p--],now);
               }
            }
         }
         else if (s[e[i]]>=b&&s[e[i]]<=2*b)
         {
            ans[++tot]=now;
            color[now]=tot;
            s[now]-=s[e[i]];
            paint(e[i],now);
         }
         else
         {
            s[now]-=s[e[i]];
            hash[now]=1;
            dfs(e[i]);
            hash[now]=0;
         }
      }
   if (s[now]<=3*b)
   {
      ans[++tot]=now;
      paint(now,0);
   }
   else
   {
      if (sum>=b)
      {
         s[now]-=sum;
         ans[++tot]=now;
         color[now]=tot;
         while (p>rec)
            paint(que[p--],now);
      }
      t=s[now];
      s[now]-=s[flag];
      s[flag]=t;
      dfs(flag);
   }
   p=rec;
   hash[now]=1;
}

int main()
{
   long i,n,x,y;
   scanf("%ld%ld",&n,&b);
   if (n<b)
      printf("0\n");
   else
   {
      for(i=1;i<n;i++)
      {
         scanf("%ld%ld",&x,&y);
         add(x,y);
         add(y,x);
      }
      getsum(1,0);
      dfs(1);
      printf("%ld\n",tot);
      for (i=1;i<=n;i++)
         printf("%ld%c",color[i],(i==n)?'\n':' ');
      for (i=1;i<=tot;i++)
         printf("%ld%c",ans[i],(i==tot)?'\n':' ');
   }
   return 0;
}
