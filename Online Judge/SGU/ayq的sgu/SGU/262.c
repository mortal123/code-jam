#include <stdio.h>
#define oo 10000000
#define max(a,b) ((a)>(b)?(a):(b))

long map[7][101]={0},set[721][7][7]={0},tmp[7][7]={0},rec[7]={0},f[102][721]={0},last[102][721]={0},ans[101]={0};
long k,tot=0;

void dfs(long now,long sum)
{
   long i,j;
   if (now==k+1)
   {
      set[++tot][0][0]=sum;
      for (i=1;i<=sum;i++)
         for (j=0;j<=tmp[i][0];j++)
            set[tot][i][j]=tmp[i][j];
   }
   else
      for (i=1;i<=sum+1;i++)
      {
         tmp[i][++tmp[i][0]]=now;
         dfs(now+1,max(i,sum));
         tmp[i][0]--;
      }
}

long find()
{
   long i,j,a,b;
   for (i=1;i<tmp[0][0];i++)
      for (j=i+1;j<=tmp[0][0];j++)
         if (tmp[i][1]>tmp[j][1])
            for (a=0;a<=max(tmp[i][0],tmp[j][0]);a++)
            {
               b=tmp[i][a];
               tmp[i][a]=tmp[j][a];
               tmp[j][a]=b;
            }
   for (i=1;;i++)
   {
      for (j=1;j<=set[i][0][0];j++)
         for (a=0;a<=set[i][j][0];a++)
            if (set[i][j][a]!=tmp[j][a])
               goto out;
      out:
      if (j>set[i][0][0])
         return i;
   }
}

int main()
{
   long i,j,a,b,n,m,sum;
   scanf("%ld%ld%ld",&n,&m,&k);
   for (i=1;i<=k;i++)
      for (j=1;j<=n*m;j++)
         scanf("%1ld",&map[i][j]);
   dfs(1,0);
   for (i=1;i<=n*m+1;i++)
      for (j=1;j<=tot;j++)
         f[i][j]=oo;
   f[1][1]=0;
   for (i=1;i<=n*m;i++)
      for (j=1;j<=tot;j++)
         if (f[i][j]<oo)
         {
            tmp[0][0]=0;
            for (a=1;a<=set[j][0][0];a++)
            {
               rec[0]=0;
               for (b=1;b<=set[j][a][0];b++)
                  if (map[set[j][a][b]][i])
                     rec[++rec[0]]=set[j][a][b];
               if (rec[0])
               {
                  tmp[0][0]++;
                  for (b=0;b<=rec[0];b++)
                     tmp[tmp[0][0]][b]=rec[b];
               }
               rec[0]=0;
               for (b=1;b<=set[j][a][0];b++)
                  if (!map[set[j][a][b]][i])
                     rec[++rec[0]]=set[j][a][b];
               if (rec[0])
               {
                  tmp[0][0]++;
                  for (b=0;b<=rec[0];b++)
                     tmp[tmp[0][0]][b]=rec[b];
               }
            }
            a=find();
            if (f[i+1][j]>f[i][j])
            {
               f[i+1][j]=f[i][j];
               last[i+1][j]=j;
            }
            if (f[i+1][a]>f[i][j]+1)
            {
               f[i+1][a]=f[i][j]+1;
               last[i+1][a]=j;
            }
         }
   printf("%ld\n",f[n*m+1][tot]);
   sum=n*m+1;
   for (i=n*m+1;i>1;i--)
   {
      ans[--sum]=(tot!=last[i][tot]);
      tot=last[i][tot];
   }
   for (i=1;i<=n*m;i++)
   {
      printf("%ld",ans[i]);
      if (i%m==0)
         printf("\n");
   }
   return 0;
}
