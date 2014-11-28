#include<stdio.h>

long d[7]={0},x[101]={0},y[101]={0},move[102]={0},link[7][7]={0},ans[101]={0};
char hash[101]={'\0'},sign[101]={'\0'};
long n,tot=0;

void search(long now)
{
   long i;
   for (i=0;i<=6;i++)
      if (link[now][i])
      {
         link[now][i]--;
         link[i][now]--;
         search(i);
      }
   move[++tot]=now;
}

int main()
{
   long i,j,p1,p2,num=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&x[i],&y[i]);
      d[x[i]]++;
      d[y[i]]++;
      link[x[i]][y[i]]++;
      link[y[i]][x[i]]++;
   }
   for (i=0;i<=6;i++)
   {
      if (d[i]%2)
      {
         num++;
         p1=i;
      }
      if (d[i])
         p2=i;
   }
   if (num>2)
      printf("No solution\n");
   else
   {
      if (num==2)
         search(p1);
      else
         search(p2);
      if (tot==n+1)
      {
         for (i=1;i<=n;i++)
         {
            for (j=1;j<=n;j++)
               if (!hash[j])
               {
                  if (x[j]==move[i]&&y[j]==move[i+1])
                  {
                     ans[i]=j;
                     hash[j]=1;
                     break;
                  }
                  else if (x[j]==move[i+1]&&y[j]==move[i])
                  {
                     sign[i]=hash[j]=1;
                     ans[i]=j;
                     break;
                  }
               }
         }
         for (i=1;i<=n;i++)
         {
            printf("%ld ",ans[i]);
            if (sign[i])
               printf("-\n");
            else
               printf("+\n");
         }
      }
      else
         printf("No solution\n");
   }
   return 0;
}
