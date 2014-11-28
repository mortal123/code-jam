#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long long put;
   long left;
}f[19][170][1001]={0,0,0};
char hash[19][170][1001]={0};
long long ans=0;
long m,left=0;

void count(struct case1 t)
{
   ans+=t.put;
   left=t.left;
}

struct case1 merge(struct case1 a,struct case1 b)
{
   return (struct case1){a.put+b.put,b.left};
}

struct case1 dfs(long i,long j,long k)
{
   long t;
   if (hash[i][j][k])
      return f[i][j][k];
   hash[i][j][k]=1;
   if (i==1)
   {
      if (k)
         f[i][j][k]=(struct case1){0,max(k-j,0)};
      else
         f[i][j][k]=(struct case1){1,max(m-j,0)};
   }
   else
   {
      f[i][j][k].left=k;
      for (t=0;t<=9;t++)
         f[i][j][k]=merge(f[i][j][k],dfs(i-1,j+t,f[i][j][k].left));
   }
   return f[i][j][k];
}

int main()
{
   long long s,q,l,r;
   long t,x,flag=0;
   scanf("%I64d%I64d%ld",&l,&r,&m);
   if (r==1000000000000000000LL)
   {
      r--;
      flag=1;
   }
   while (l<=r)
   {
      s=x=1;
      while (l%(s*10)==0&&l+s*10<=r+1)
      {
         s*=10;
         x++;
      }
      q=l;
      t=0;
      while (q)
      {
         t+=q%10;
         q/=10;
      }
      count(dfs(x,t,left));
      l+=s;
   }
   if (flag&&!left)
   {
      ans++;
      left=m-1;
   }
   printf("%I64d\n",ans-!!left);
   return 0;
}
