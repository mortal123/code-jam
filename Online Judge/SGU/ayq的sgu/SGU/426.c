#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

long ans[100001]={0},st[21][100001]={0},a[100002]={0},h[100001]={0},height[100001]={0},prank[100001]={0},rank[200001]={0},d[100001]={0},sa[100001]={0},control[50001]={0},head2[50001]={0},e2[50001]={0},next2[50001]={0},head[100001]={0},e[100001]={0},next[100001]={0};
char hash[50001]={0};
long totm=0;

void add(long a,long b,long head[],long e[],long next[])
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
}

long rmq(long a,long b)
{
   long x,y,t=0;
   x=min(a,b);
   y=max(a,b)-1;
   while ((1<<t+1)<=y-x+1)
      t++;
   return min(st[t][x],st[t][y-(1<<t)+1]);
}

int main()
{
   long i,j,x,n,m,k,s,t,tot;
   scanf("%ld%ld%ld",&n,&m,&k);
   tot=max(2*n,m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&rank[i]);
      a[i]=a[i+n]=rank[i+n]=rank[i];
      add(rank[i],i,head2,e2,next2);
      hash[rank[i]]=1;
   }
   for (i=0;i<m;i++)
      if (hash[i])
      {
         j=(i+m-1)%m;
         while (!hash[j])
         {
            control[i]++;
            j=(j+m-1)%m;
         }
      }
   a[2*n+1]=-1;
   for (i=2*n+1;i<=4*n;i++)
      rank[i]=-1;
   for (i=0;1+(1<<i)<=2*n;i++)
   {
      totm=s=0;
      memset(head,0,sizeof(long)*(tot+1));
      for (j=1;j+(1<<i)<=2*n;j++)
         add(rank[j+(1<<i)]+1,j,head,e,next);
      for (;j<=2*n;j++)
         add(0,j,head,e,next);
      for (j=0;j<=tot;j++)
         for (x=head[j];x;x=next[x])
            d[++s]=e[x];
      totm=s=0;
      memset(head,0,sizeof(long)*(tot+1));
      for (j=2*n;j>=1;j--)
         add(rank[d[j]],d[j],head,e,next);
      for (j=0;j<=tot;j++)
         for (x=head[j];x;x=next[x])
            d[++s]=e[x];
      s=0;
      for (j=1;j<=2*n;j++)
      {
         if (j==1||rank[d[j]]!=rank[d[j-1]]||rank[d[j]+(1<<i)]!=rank[d[j-1]+(1<<i)])
            s++;
         prank[d[j]]=s;
      }
      for (j=1;j<=2*n;j++)
         rank[j]=prank[j];
   }
   for (i=1;i<=2*n;i++)
      sa[rank[i]]=i;
   for (i=1;i<=2*n;i++)
   {
      if (rank[i]>1)
         for (h[i]=max(h[i-1]-1,0);a[i+h[i]]==a[sa[rank[i]-1]+h[i]];h[i]++);
      height[rank[i]]=h[i];
   }
   for (i=1;i<2*n;i++)
      st[0][i]=height[i+1];
   for (i=1;1+(1<<i-1)<2*n;i++)
      for (j=1;j<2*n;j++)
      {
         st[i][j]=st[i-1][j];
         if (j+(1<<i-1)<2*n&&st[i-1][j+(1<<i-1)]<st[i][j])
            st[i][j]=st[i-1][j+(1<<i-1)];
      }
   for (i=0;i<m;i++)
      if (hash[i])
      {
         t=e2[head2[i]];
         for (j=next2[head2[i]];j;j=next2[j])
         {
            s=rmq(rank[t],rank[e2[j]]);
            if (s<n&&(a[(t+s-1)%n+1]+m-a[t])%m>(a[(e2[j]+s-1)%n+1]+m-a[e2[j]])%m)
               t=e2[j];
         }
         s=(k+t-2)%n+1;
         for (j=0;j<=control[i];j++)
            ans[(m-a[t]+j)%m]=(a[s]+m-a[t]+j)%m;
      }
   for (i=0;i<m;i++)
      printf("%ld\n",ans[i]);
   return 0;
}
