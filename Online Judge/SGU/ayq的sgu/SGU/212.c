#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

long l[1501][1501]={0},r[1501][1501]={0},f[1501][1501]={0},num[1501][1501]={0},d[1501]={0},flow[1501]={0},dis[1501]={0},p[1501]={0},q[1501]={0},gap[1501]={0},last[1501]={0},ans[300001]={0};
char hash[1501]={'\0'},str[31]={'\0'};

int main()
{
   long i,j,n,m,x,s,t,a,b,c,min,st=1,en=1,now,tmp,top;
   scanf("%ld%ld%ld",&n,&m,&x);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&dis[i]);
      if (dis[i]==1)
         s=i;
      else if (dis[i]==x)
         t=i;
      gap[dis[i]]++;
   }
   scanf("\n");
   for (i=1;i<=m;i++)
   {
      gets(str);
      a=b=c=0;
      for (j=0;str[j]>='0'&&str[j]<='9';j++)
         a=a*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         b=b*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         c=c*10+str[j]-'0';
      l[a][++p[a]]=b;
      l[b][n+1-(++q[b])]=a;
      num[a][p[a]]=i;
      r[a][b]=c;
   }
   d[1]=s;
   hash[s]=1;
   flow[s]=oo;
   while (st<=en)
   {
      now=d[st++];
      for (i=1;i<=p[now];i++)
      {
         tmp=min(flow[now],r[now][l[now][i]]-f[now][l[now][i]]);
         f[now][l[now][i]]+=tmp;
         flow[l[now][i]]+=tmp;
         flow[now]-=tmp;
         if (!hash[l[now][i]])
         {
            d[++en]=l[now][i];
            hash[l[now][i]]=1;
         }
      }
   }
   memset(hash,0,sizeof(hash));
   st=en=hash[t]=1;
   d[1]=t;
   flow[t]=0;
   while (st<=en)
   {
      now=d[st++];
      for (i=1;i<=q[now];i++)
      {
         tmp=min(flow[now],f[l[now][n+1-i]][now]);
         f[l[now][n+1-i]][now]-=tmp;
         flow[l[now][n+1-i]]+=tmp;
         flow[now]-=tmp;
         if (!hash[l[now][n+1-i]])
         {
            d[++en]=l[now][n+1-i];
            hash[l[now][n+1-i]]=1;
         }
      }
   }
   memset(hash,'\0',sizeof(hash));
   for (i=s;!hash[s];)
   {
      for (j=1;j<=p[i];j++)
         if (r[i][l[i][j]]-f[i][l[i][j]]&&!hash[l[i][j]])
         {
            last[l[i][j]]=i;
            i=l[i][j];
            goto out;
         }
      if (gap[dis[i]]==1)
         break;
      gap[dis[i]]--;
      hash[i]=1;
      i=last[i];
      out:
      if (i==t)
      {
         min=oo;
         for (;last[i];i=last[i])
            min=min(min,r[last[i]][i]-f[last[i]][i]);
         for (i=t;last[i];i=last[i])
            f[last[i]][i]+=min;
      }
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=p[i];j++)
         ans[num[i][j]]=f[i][l[i][j]];
   str[29]='\0';
   for (i=1;i<=m;i++)
   {
      top=29;
      if (!ans[i])
         str[--top]='0';
      else
         while (ans[i])
         {
            str[--top]=ans[i]%10+'0';
            ans[i]/=10;
         }
      puts(str+top);
   }
   return 0;
}
