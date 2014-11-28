#include <stdio.h>

int f[2][5][65537];
char str[9][33];
int n,a=0;

void dfs(int now,int l,int pre,int v,int cur)
{
   if (now>4*l+4)
      f[a][l+1][cur]+=f[a][l][pre];
   else if (now>4*l)
   {
      if (!(cur&(1<<(now-4*l)*(l+1)-1))&&!(cur&(1<<(now-4*l)*(l+1)%(4*(l+1)))))
         dfs(now+1,l,pre,v,cur+(1<<(now-4*l)*(l+1)-1)+(1<<(now-4*l)*(l+1)%(4*(l+1))));
      dfs(now+1,l,pre,v,cur);
   }
   else if (v&(1<<now-1))
   {
      if (!(cur&(1<<(now-1)/l*(l+1)+(now-1)%l)))
         dfs(now+1,l,pre,v,cur+(1<<(now-1)/l*(l+1)+(now-1)%l));
      if (!(cur&(1<<(now-1)/l*(l+1)+(now-1)%l+1)))
         dfs(now+1,l,pre,v,cur+(1<<(now-1)/l*(l+1)+(now-1)%l+1));
   }
   else
      dfs(now+1,l,pre,v,cur);
}

void work()
{
   int i,j,k,l,pre,cur;
   f[a][0][0]=1;
   for (i=0;i<n;i++)
      for (j=0;j<(1<<4*i);j++)
         if (f[a][i][j])
         {
            pre=cur=0;
            for (k=0;k<4;k++)
            {
               for (l=1;l<=i;l++)
                  if (str[i+1][k*(2*i+1)+l*2]=='*'&&!(j&(1<<k*i+l-1)))
                     goto out;
                  else if (str[i+1][k*(2*i+1)+l*2]!='*'&&(j&(1<<k*i+l-1)))
                     pre+=1<<k*i+l-1;
               for (l=1;l<=i+1;l++)
                  if (str[i+1][k*(2*i+1)+l*2-1]=='*')
                     cur+=1<<k*(i+1)+l-1;
            }
            dfs(1,i,j,pre,cur);
            out:;
         }
}

int main()
{
   int i,j;
   long long ans=0;
   scanf("%d\n",&n);
   for (i=1;i<=n<<1;i++)
      gets(str[i]+1);
   work();
   for (i=1;i<=n;i++)
      for (j=1;j<=8*i-4;j++)
         str[i][j]=str[2*n-i+1][j];
   a=1;
   work();
   for (i=0;i<1<<4*n;i++)
      ans+=f[0][n][i]*f[1][n][i];
   printf("%I64d\n",ans);
   return 0;
}
