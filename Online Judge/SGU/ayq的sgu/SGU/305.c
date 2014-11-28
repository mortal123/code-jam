#include <stdio.h>

struct case1
{
   long a,b;
}p[301]={{0,0}};
long ans[301]={0},hash[3001]={0},r[3001]={0},f[3001]={0};
long m,tot=0,flag=0;

long find(long now)
{
   long i;
   for (i=1;i<=tot;i++)
      if (r[i]==now)
         return i;
   r[++tot]=now;
   return tot;
}

long match(long now)
{
   long i,pos;
   for (i=p[now].b;i>=1&&i<=m;i+=p[now].a)
   {
      pos=find(i);
      if (hash[pos]!=flag)
      {
         hash[pos]=flag;
         if (!f[pos]||match(f[pos]))
         {
            f[pos]=now;
            return 1;
         }
      }
      if (p[now].a==0)
         break;
   }
   return 0;
}

int main()
{
   long i,j,k,n;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
   {
      scanf("%ld%ld",&p[i].a,&p[i].b);
      if (p[i].a>0&&p[i].b<1)
         p[i].b+=(p[i].a-p[i].b)/p[i].a*p[i].a;
      else if (p[i].a<0&&p[i].b>m)
         p[i].b-=(p[i].b-m-p[i].a-1)/(-p[i].a)*(-p[i].a);
   }
   for (i=1;i<=n;i++)
   {
      flag++;
      match(i);
   }
   for (i=1;i<=tot;i++)
      if (f[i])
         ans[f[i]]=r[i];
   j=0;
   for (i=1;i<=n;i++)
      if (!ans[i])
      {
         j++;
         while (1)
         {
            for (k=1;k<=n&&ans[k]!=j;k++);
            if (k>n)
            {
               ans[i]=j;
               break;
            }
            j++;
         }
      }
   for (i=1;i<=n;i++)
      printf("%ld%c",ans[i],(i==n)?'\n':' ');
   return 0;
}
