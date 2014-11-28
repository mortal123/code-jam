#include <stdio.h>

long a[2001]={0},rec[21][2001]={0};
long n,p,tot=0;

void dfs(long now,long add)
{
   long i,s=add;
   if (now>n)
   {
      tot++;
      for (i=1;i<=n;i++)
         rec[tot][i]=a[i];
   }
   else
   {
      for (i=2;i<=(now+1)/2;i++)
         s+=2*a[i]*a[now-i+1];
      if (now&1)
         s-=a[(now+1)/2]*a[(now+1)/2];
      for (i=(now==n);i<p;i++)
         if ((s+2*i*a[1])%p==i)
         {
            a[now]=i;
            dfs(now+1,(s+2*i*a[1])/p);
         }
   }
}

int main()
{
   long i,j;
   scanf("%ld%ld",&p,&n);
   for(i=0;i<p;i++)
      if (i*i%p==i)
      {
         a[1]=i;
         dfs(2,i*i/p);
      }
   printf("%ld\n",tot);
   for (i=1;i<=tot;i++)
   {
      for (j=n;j>=1;j--)
         if (rec[i][j]<=9)
            printf("%ld",rec[i][j]);
         else
            printf("%c",rec[i][j]-10+'A');
      printf("\n");
   }
   return 0;
}
