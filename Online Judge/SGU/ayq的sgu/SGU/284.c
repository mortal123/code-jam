#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

char str[105]={'\0'},link[31][31]={'\0'},tmp[1505]={'\0'},pre[31][105]={'\0'},last[31][105]={'\0'};
long l[31]={0},len[31]={0},du[31]={0},p[31][505]={0},d[31]={0},num[31][601]={0},w[31]={0},L[31]={0};
long tot,n;

void add(long a,long b)
{
   long i;
   w[a]=max(w[a],w[b])+1;
   for (i=1;i<=w[a];i++)
   {
      num[a][i]+=num[b][i]+num[a][i-1]/10;
      num[a][i-1]%=10;
   }
   while (!num[a][w[a]])
      w[a]--;
}

void match(long now,long i,long t)
{
   long j;
   for (;t;i--)
      if (p[now][i]<=n)
      {
         for (j=L[p[now][i]];j>=1&&t;j--,t--)
            if (str[t]!=last[p[now][i]][j])
               return;
      }
      else if (str[t]!=p[now][i]-n-1+'a')
         return;
      else
         t--;
   add(now,0);
}

int main()
{
   long i,j,k,t,now,st=1,en=0;
   scanf("%ld\n%s",&n,str+1);
   tot=strlen(str+1);
   for (i=1;i<=n;i++)
   {
      scanf("%ld",&l[i]);
      gets(tmp+1);
      t=0;
      for (j=1;j<=l[i];j++)
      {
         t+=2;
         if (tmp[t]=='a'||tmp[t]=='b')
            p[i][j]=n+1+(tmp[t]=='b');
         else
         {
            if (tmp[t+1]>='0'&&tmp[t+1]<='9')
            {
               p[i][j]=(tmp[t]-'0')*10+tmp[t+1]-'0';
               t++;
            }
            else
               p[i][j]=tmp[t]-'0';
            if (!link[p[i][j]][i])
            {
               link[p[i][j]][i]=1;
               du[i]++;
            }
         }
      }
   }
   for (i=1;i<=n;i++)
      if (!du[i])
         d[++en]=i;
   num[0][1]=w[0]=1;
   while (st<=en)
   {
      now=d[st++];
      for (i=1;i<=l[now];i++)
         if (p[now][i]<=n)
         {
            add(now,p[now][i]);
            if (len[now]+L[p[now][i]]>=tot)
               for (j=max(tot-len[now],1);j<=L[p[now][i]];j++)
               {
                  for (k=j;k>=1&&pre[p[now][i]][k]==str[tot+k-j];k--);
                  if (!k)
                     match(now,i-1,tot-j);
               }
            len[now]=min(len[now]+len[p[now][i]],oo);
         }
         else
         {
            len[now]=min(len[now]+1,oo);
            if (len[now]>=tot)
               match(now,i,tot);
         }
      L[now]=min(len[now],tot-1);
      t=1;
      for (i=1;t<=L[now];i++)
         if (p[now][i]<=n)
            for (j=1;j<=L[p[now][i]]&&t<=L[now];j++)
               pre[now][t++]=pre[p[now][i]][j];
         else
            pre[now][t++]='a'+p[now][i]-n-1;
      t=L[now];
      for (i=l[now];t;i--)
         if (p[now][i]<=n)
            for (j=L[p[now][i]];j>=1&&t;j--)
               last[now][t--]=last[p[now][i]][j];
         else
            last[now][t--]='a'+p[now][i]-n-1;
      for (i=1;i<=n;i++)
         if (link[now][i])
         {
            du[i]--;
            if (!du[i])
               d[++en]=i;           
         }
   }
   for (i=w[n];i>=2;i--)
      printf("%ld",num[n][i]);
   printf("%ld\n",num[n][1]);
   return 0;
}
