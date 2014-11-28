#include <stdio.h>
#define mod 1000007

struct case1
{
   long s,t;
   long w[4];
}p[1000008]={0,0,0};
long head[1000008]={0},next[1000008]={0},l[8][4]={{0,0,0,0},{0,0,1,1},{0,1,0,1},{1,0,0,1},{1,1,0,2},{1,0,1,2},{0,1,1,2},{1,1,1,3}};
long long f[1000008]={0};
long n,tot=0;

long key(struct case1 x)
{
   long i,s=x.s*25+x.t;
   for (i=0;i<4;i++)
      s=(s*25+x.w[i])%mod;
   if (s<0||s>=mod)
      i=1;
   return s;
}

long cmp(struct case1 x,struct case1 y)
{
   long i;
   if (x.s!=y.s||x.t!=y.t)
      return 0;
   for (i=0;i<4;i++)
      if (x.w[i]!=y.w[i])
         return 0;
   return 1;
}

long find(struct case1 x)
{
   long i,y=key(x);
   for (i=head[y];i&&!cmp(p[i],x);i=next[i]);
   if (i)
      return i;
   p[++tot]=x;
   next[tot]=head[y];
   head[y]=tot;
   return 0;
}

void dp(long x,struct case1 y,long t)
{
   long i,key;
   struct case1 tmp;
   if ((y.s)&1)
      for (i=0;i<8;i++)
      {
         if (y.w[l[i][3]]&&(t==1||l[i][0]==!!(p[x].t&(1<<(t*2-3))))&&(t==(y.s+1)/2||l[i][1]==!!(p[x].t&(1<<(t*2-2)))))
         {
            y.w[l[i][3]]--;
            y.t+=(l[i][2]<<(t-1));
            if (t==(y.s+1)/2)
            {
               if (y.s==2*n-1)
                  f[x]++;
               else
               {
                  key=find(y);
                  if (!key)
                  {
                     tmp=y;
                     tmp.t=0;
                     tmp.s++;
                     dp(key=tot,tmp,1);
                  }
                  f[x]+=f[key];
               }
            }
            else
               dp(x,y,t+1);
            y.w[l[i][3]]++;
            y.t-=l[i][2]*(1<<(t-1));
         }
      }
   else
      for (i=0;i<8;i++)
         if (y.w[l[i][3]]&&l[i][0]==!!(p[x].t&(1<<(t-1))))
         {
            y.w[l[i][3]]--;
            y.t+=(l[i][1]<<(2*t-2))+(l[i][2]<<(2*t-1));
            if (t==(y.s+1)/2)
            {
               key=find(y);
               if (!key)
               {
                  tmp=y;
                  tmp.t=0;
                  tmp.s++;
                  dp(key=tot,tmp,1);
               }
               f[x]+=f[key];
            }
            else
               dp(x,y,t+1);
            y.w[l[i][3]]++;
            y.t-=(l[i][1]<<(2*t-2))+(l[i][2]<<(2*t-1));
         }
}

int main()
{
   struct case1 t={0};
   scanf("%ld%ld%ld%ld%ld",&n,&t.w[0],&t.w[1],&t.w[2],&t.w[3]);
   find(t);
   t.s=1;
   dp(1,t,1);
   printf("%I64d\n",f[1]);
   return 0;
}
