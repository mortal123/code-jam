#include <stdio.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct edge
{
   long a,b,c;
}p[401]={{0,0,0}};
long w[401][401]={0},fx[401]={0},fy[401]={0},father[401]={0},link[61][61]={0},stack[401]={0};
char hashx[401]={'\0'},hashy[401]={'\0'};
long n,p2;

long match(long now)
{
   long i;
   hashx[now]=1;
   for (i=1;i<=p2;i++)
      if(!hashy[i])
      {
         if (fx[now]+fy[i]==w[now][i])
         {
            hashy[i]=1;
            if(!father[i]||match(father[i]))
            {
               father[i]=now;
               return 1;
            }
         }
         else
            stack[i]=min(stack[i],fx[now]+fy[i]-w[now][i]);
      }
   return 0;
}

long dfs(long a,long b,long last,long num)
{
   long i;
   if(a==b)
      return 1;
   for(i=1;i<=n;i++)
      if (link[a][i]&&i!=last&&dfs(i,b,a,num))
      {
         w[link[a][i]][num-n+1]=p[link[a][i]].c-p[num].c;
         return 1;
      }
   return 0;
}

int main()
{
   long i,j,m,p1,min;
   scanf("%ld%ld",&n,&m);
   for(i=1;i<=m;i++)
      scanf("%ld%ld%ld",&p[i].a,&p[i].b,&p[i].c);
   for(i=1;i<n;i++)
      link[p[i].a][p[i].b]=link[p[i].b][p[i].a]=i;
   for(i=n;i<=m;i++)
      dfs(p[i].a,p[i].b,0,i);
   p1=n-1;
   p2=max(p1,m-n+1);
   for (i=1;i<=p1;i++)
   {
      fx[i]=-oo;
      for (j=1;j<=p2;j++)
         fx[i]=max(fx[i],w[i][j]);
   }
   for (i=1;i<=p1;i++)
   {
      for (j=1;j<=p2;j++)
         stack[j]=oo;
      while (1)
      {
         memset(hashx,'\0',sizeof(hashx));
         memset(hashy,'\0',sizeof(hashy));
         if (match(i))
            break;
         min=oo;
         for (j=1;j<=p2;j++)
            if (!hashy[j])
               min=min(min,stack[j]);
         for (j=1;j<=p1;j++)
            if (hashx[j])
               fx[j]-=min;
         for (j=1;j<=p2;j++)
            if (hashy[j])
               fy[j]+=min;
      }
   }
   for(i=1;i<n;i++)
      printf("%ld\n",p[i].c-fx[i]);
   for(i=n;i<=m;i++)
      printf("%ld\n",p[i].c+fy[i-n+1]);
   return 0;
}
