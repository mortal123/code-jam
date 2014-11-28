#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long a,b,c;
}p[21]={0,0,0};
long rec[1001][10001]={0},ans[10001]={0},l[1001]={0},num[1001]={0};
char hash[1001]={0};
long k;

void dfs(long now,long s,long left)
{
   if (now>k)
      num[left]+=s;
   else
   {
      dfs(now+1,s,left);
      if (!hash[p[now].a]&&!hash[p[now].b]&&!hash[p[now].c])
      {
         hash[p[now].a]=hash[p[now].b]=hash[p[now].c]=1;
         dfs(now+1,-s,left-1);
         hash[p[now].a]=hash[p[now].b]=hash[p[now].c]=0;
      }
   }
}

int main()
{
   long i,j,t,n,lans=0;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=k;i++)
      scanf("%ld%ld%ld",&p[i].a,&p[i].b,&p[i].c);
   rec[0][1]=l[0]=1;
   for (i=1;i<=n;i++)
   {
      t=(i*3-1)*(i*3-2)/2;
      l[i]=l[i-1]+8;
      for (j=1;j<=l[i];j++)
      {
         rec[i][j]=rec[i-1][j]*t+rec[i][j-1]/10;
         rec[i][j-1]%=10;
      }
      while (!rec[i][l[i]])
         l[i]--;
   }
   dfs(1,1,n);
   for (i=max(0,n-k);i<=n;i++)
      if (num[i]>0)
      {
         lans=max(lans,l[i])+1;
         for (j=1;j<=lans;j++)
         {
            ans[j]+=rec[i][j]*num[i]+ans[j-1]/10;
            ans[j-1]%=10;
         }
         while (!ans[lans])
            lans--;
      }
   for (i=max(0,n-k);i<=n;i++)
      if (num[i]<0)
      {
         lans=max(lans,l[i]);
         for (j=1;j<=lans;j++)
         {
            ans[j]+=rec[i][j]*num[i]+(ans[j-1]+10000000)/10-1000000;
            ans[j-1]=(ans[j-1]+10000000)%10;
         }
         while (lans&&!ans[lans])
            lans--;
      }
   for (i=lans;i>=2;i--)
      printf("%ld",ans[i]);
   printf("%ld\n",ans[1]);
   return 0;
}
