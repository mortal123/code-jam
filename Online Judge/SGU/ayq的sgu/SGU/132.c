#include <stdio.h>
#define oo 1000000000

long f[2][16385]={0},w[75]={0},a[4][8]={0},head[16385]={0},next[547427]={0};
char v[547427]={'\0'},str[9]={'\0'};
short e[547427]={0};
long totm=0,n,m;

void add(long a,long b,long c)
{
   e[++totm]=b;
   next[totm]=head[a];
   head[a]=totm;
   v[totm]=c;
}

void dfs(long l,long old,long s)
{
   long i,x,y;
   if(l<=2*m)
   {
      x=(l-1)/m+1;
      y=(l-1)%m+1;
      dfs(l+1,old,s);
      if(!a[x][y]&&y<m&&!a[x][y+1])
      {
         a[x][y]=a[x][y+1]=1;
         dfs(l+1,old,s+1);
         a[x][y]=a[x][y+1]=0;
      }
      if(!a[x][y]&&!a[x+1][y])
      {
         a[x][y]=a[x+1][y]=1;
         dfs(l+1,old,s+1);
         a[x][y]=a[x+1][y]=0;
      }
   }
   else
   {
      x=y=0;
      for(i=1;i<=m;i++)
      {
         x+=(1<<(i-1))*a[2][i];
         y+=(1<<(i-1))*a[3][i];
         if(a[1][i]==0&&(a[2][i]==0||i<m&&a[1][i+1]==0))
            return;
      }
      for(i=head[old];i;i=next[i])
         if(e[i]==(y<<m)+x)
         {
            if(s<v[i])
               v[i]=s;
            return;
         }
      add(old,(y<<m)+x,s);
   }
}

int main()
{
   long i,j,k;
   scanf("%ld%ld",&n,&m);
   w[n+1]=w[n+2]=(1<<m)-1;
   for(i=1;i<=n;i++)
   {
      scanf("%s",str);
      for(j=0;j<m;j++)
         w[i]+=(1<<j)*(str[j]=='*');
   }
   for(i=0;i<=1;i++)
      for(j=0;j<(1<<(2*m));j++)
         f[i][j]=oo;
   f[0][w[1]+(w[2]<<m)]=0;
   for(i=0;i<n;i++)
   {
      for(j=0;j<(1<<(2*m));j++)
         if(f[i&1][j]<oo&&(j&(w[i+1]+(w[i+2]<<m)))==(w[i+1]+(w[i+2]<<m)))
         {
            if(!head[j])
            {
               for (k=0;k<m;k++)
               {
                  a[1][k+1]=!!(j&(1<<k));
                  a[2][k+1]=!!(j&(1<<(m+k)));
               }
               dfs(1,j,0);
            }
            for(k=head[j];k;k=next[k])
               if(!((e[k]>>m)&w[i+3])&&f[i&1][j]+v[k]<f[(i+1)&1][e[k]+(w[i+3]<<m)])
                  f[(i+1)&1][e[k]+(w[i+3]<<m)]=f[i&1][j]+v[k];
         }
      for(j=0;j<(1<<(2*m));j++)
         f[i&1][j]=oo;
   }
   printf("%ld\n",f[n&1][(1<<(2*m))-1]);
   return 0;
}
