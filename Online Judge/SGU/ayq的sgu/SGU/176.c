#include <stdio.h>
#define oo 1000000000

long r[103][103]={0},f[103][103]={0},num[101][101]={0},gap[103]={0},dis[103]={0},last[103]={0},sum[101]={0},ans[20001]={0};
long n;

long sap()
{
   long i,j,min,flow=0;
   memset(dis,0,sizeof(dis));
   memset(gap,0,sizeof(gap));
   memset(f,0,sizeof(f));
   gap[0]=n+2;
   for (i=n+1;dis[n+1]<n+2;)
   {
      for (j=1;j<=n+2;j++)
         if (r[i][j]-f[i][j]&&dis[j]==dis[i]-1)
         {
            last[j]=i;
            i=j;
            break;
         }
      if (i==n+2)
      {
         min=oo;
         for (i=n+2;last[i];i=last[i])
            if (r[last[i]][i]-f[last[i]][i]<min)
               min=r[last[i]][i]-f[last[i]][i];
         flow+=min;
         for (i=n+2;last[i];i=last[i])
         {
            f[last[i]][i]+=min;
            f[i][last[i]]-=min;
         }
      }
      else if (j>n+2)
      {
         if (gap[dis[i]]==1)
            break;
         min=oo;
         for (j=1;j<=n+2;j++)
            if (r[i][j]-f[i][j]&&dis[j]<min)
               min=dis[j];
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
   return flow;
}

int main()
{
   long i,j,m,a,b,c,d,left=-1,right=0,mid,s=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      if (a==1)
         right+=c;
      if (d)
      {
         sum[a]-=c;
         sum[b]+=c;
         ans[i]=c;
      }
      else
      {
         num[a][b]=i;
         r[a][b]+=c;
      }
   }
   for (i=1;i<=n;i++)
      if (sum[i]>0)
      {
         s+=sum[i];
         r[n+1][i]+=sum[i];
      }
      else if (sum[i]<0)
         r[i][n+2]-=sum[i];
   r[n][1]+=oo;
   if (sap()!=s)
      printf("Impossible\n");
   else
   {
      r[n][1]-=oo;
      while (left<right-1)
      {
         mid=(left+right)>>1;
         r[n][1]+=mid;
         if (sap()!=s)
            left=mid;
         else
            right=mid;
         r[n][1]-=mid;
      }
      r[n][1]+=right;
      sap();
      for (i=1;i<=n;i++)
         for (j=1;j<=n;j++)
            if (num[i][j])
               ans[num[i][j]]=f[i][j];
      printf("%ld\n",right);
      for (i=1;i<=m;i++)
         printf("%ld%c",ans[i],(i==m)?'\n':' ');
   }
   return 0;
}
