#include <stdio.h>
#define oo 1000000000

long head[203]={0},gap[203]={0},dis[203]={0},last[203]={0},laste[203]={0},sum[203]={0},e[240004]={0},next[240004]={0},r[240004]={0},num[240004]={0},ans[80001]={0};
long totm=1;

void add(long a,long b,long c,long d)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   r[totm]=c;
   num[totm]=d;
   e[++totm]=a;
   next[totm]=head[b];
   head[b]=totm;
}

int main()
{
   long i,j,n,m,a,b,c,d,min,flow=0,s=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      if (c)
      {
         sum[a]-=c;
         sum[b]+=c;
         ans[i]+=c;
      }
      if (d-c)
         add(a,b,d-c,i);
   }
   for (i=1;i<=n;i++)
      if (sum[i]>0)
      {
         s+=sum[i];
         add(n+1,i,sum[i],0);
      }
      else if (sum[i]<0)
         add(i,n+2,-sum[i],0);
   gap[0]=n+2;
   for (i=n+1;dis[n+1]<n+2;)
   {
      for (j=head[i];j;j=next[j])
         if (r[j]&&dis[e[j]]==dis[i]-1)
         {
            last[e[j]]=i;
            laste[e[j]]=j;
            i=e[j];
            break;
         }
      if (i==n+2)
      {
         min=oo;
         for (i=n+2;last[i];i=last[i])
            if (r[laste[i]]<min)
               min=r[laste[i]];
         flow+=min;
         for (i=n+2;last[i];i=last[i])
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
         if (min>n+2)
            min=n+2;
         gap[dis[i]]--;
         dis[i]=min;
         gap[dis[i]]++;
         if (i!=n+1)
            i=last[i];
      }
   }
   if (flow!=s)
      printf("NO\n");
   else
   {
      printf("YES\n");
      for (i=1;i<=totm;i++)
         if (num[i])
            ans[num[i]]+=r[i^1];
      for (i=1;i<=m;i++)
         printf("%ld\n",ans[i]);
   }
   return 0;
}
