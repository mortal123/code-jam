#include <stdio.h>
#include <stdlib.h>
#define lowbit(a) ((a)&(-(a)))

int t[10],rec[40],num[513],mat[7][6][7],pos[7][7],con[40][2],sum[40],avi[40],left[40];
char str[51],can[6][35][513][10];
int s,flag=0;

void dfs(int now)
{
   int i,x;
   if (now>s)
      flag=1;
   else
      for (x=1;x<=9;x++)
      {
         i=t[x];
         if (can[left[con[now][0]]][sum[con[now][0]]][avi[con[now][0]]][i]&&can[left[con[now][1]]][sum[con[now][1]]][avi[con[now][1]]][i])
         {
            rec[now]=i;
            left[con[now][0]]--;
            sum[con[now][0]]-=i;
            avi[con[now][0]]-=(1<<i-1);
            left[con[now][1]]--;
            sum[con[now][1]]-=i;
            avi[con[now][1]]-=(1<<i-1);
            dfs(now+1);
            if (flag)
               return;
            left[con[now][0]]++;
            sum[con[now][0]]+=i;
            avi[con[now][0]]+=(1<<i-1);
            left[con[now][1]]++;
            sum[con[now][1]]+=i;
            avi[con[now][1]]+=(1<<i-1);
         }
      }
}

int main()
{
   int n,m,i,j,k,l,a,b,o=0;
   for (i=1;i<=9;i++)
      t[i]=i;
   for (i=1;i<=9;i++)
   {
      a=rand()%9+1;
      if (a!=i)
      {
         t[i]^=t[a];
         t[a]^=t[i];
         t[i]^=t[a];
      }
   }
   for (i=1;i<512;i++)
      num[i]=num[i-lowbit(i)]+1;
   for (i=1;i<=5;i++)
      for (j=1;j<=35;j++)
         for (k=1;k<512;k++)
            if (num[k]>=i)
               for (l=1;l<=9;l++)
                  if (k&(1<<l-1))
                  {
                     s=0;
                     b=1;
                     for (a=1;a<i;a++)
                     {
                        while (b==l||!(k&(1<<b-1)))
                           b++;
                        s+=b++;
                     }
                     if (s+l<=j)
                     {
                        s=0;
                        b=9;
                        for (a=1;a<i;a++)
                        {
                           while (b==l||!(k&(1<<b-1)))
                              b--;
                           s+=b--;
                        }
                        if (s+l>=j)
                           can[i][j][k][l]=1;
                     }
                  }
   s=0;
   scanf("%d%d\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      for (j=1;j<=m;j++)
         if (str[6*j-5]=='.')
            pos[i][j]=++s;
         else
         {
            if (str[6*j-5]!='X')
               mat[i][j][0]=10*(str[6*j-5]-'0')+str[6*j-4]-'0';
            if (str[6*j-2]!='X')
               mat[i][j][1]=10*(str[6*j-2]-'0')+str[6*j-1]-'0';
         }
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
      {
         if (mat[i][j][0])
         {
            sum[++o]=mat[i][j][0];
            avi[o]=511;
            for (k=i+1;k<=n&&pos[k][j];k++)
            {
               con[pos[k][j]][0]=o;
               left[o]++;
            }
         }
         if (mat[i][j][1])
         {
            sum[++o]=mat[i][j][1];
            avi[o]=511;
            for (k=j+1;k<=m&&pos[i][k];k++)
            {
               con[pos[i][k]][1]=o;
               left[o]++;
            }
         }
      }
   dfs(1);
   for (i=1;i<=n;i++)
      for (j=1;j<=m;j++)
         if (pos[i][j])
            printf("%d%c",rec[pos[i][j]],(j==m)?'\n':' ');
         else
            printf("_%c",(j==m)?'\n':' ');
   return 0;
}
