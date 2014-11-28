#include<stdio.h>

struct case1
{
   long pos,k;
}q[5001]={{0,0}};
char hash[65]={0};
long ans[5001]={0};

void qs(long x,long y)
{
   long i=x,j=y;
   struct case1 t=q[(x+y)>>1];
   if (x>=y)
      return;
   q[(x+y)>>1]=q[x];
   while (i<j)
   {
      while (i<j&&q[j].k>t.k)
         j--;
      if (i<j)
         q[i++]=q[j];
      while (i<j&&q[i].k<t.k)
         i++;
      if (i<j)
         q[j--]=q[i];
   }
   q[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   long i,n,k,t,s,last=0,p=1,sum=0;
   scanf("%ld%ld",&n,&k);
   for (i=1;i<=k;i++)
   {
      q[i].pos=i;
      scanf("%ld",&q[i].k);
   }
   qs(1,k);
   for (i=1;i<=n;i++)
   {
      hash[(i-1)%65]=0;
      if (hash[i%65]==0)
         sum++;
      while (p<=k&&q[p].k==sum)
         ans[q[p++].pos]=i;
      if (i%10)
         s=last+2;
      else
      {
         t=s=i;
         while (t)
         {
            s+=t%10;
            t/=10;
         }
      }
      last=s;
      if (s<=n)
         hash[s%65]=1;
   }
   printf("%ld\n%ld",sum,ans[1]);
   for (i=2;i<=k;i++)
      printf(" %ld",ans[i]);
   printf("\n");
   return 0;
}
