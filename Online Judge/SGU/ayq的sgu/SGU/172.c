#include<stdio.h>

long f[201]={0},r[201]={0},ans[201]={0};

long getf(long now)
{
   long t=f[now];
   if (f[now]==now)
      return now;
   f[now]=getf(f[now]);
   r[now]^=r[t];
   return f[now];
}

int main()
{
   long i,n,m,a,b,fa,fb,tot=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      f[i]=i;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld",&a,&b);
      fa=getf(a);
      fb=getf(b);
      if (fa==fb)
      {
         if (r[a]==r[b])
         {
            printf("no\n");
            goto end;
         }
      }
      else
      {
         f[fa]=fb;
         if (r[a]==r[b])
            r[fa]=1;
      }
   }
   for (i=1;i<=n;i++)
   {
      getf(i);
      if (r[i])
         ans[++tot]=i;
   }
   printf("yes\n%ld\n%ld",tot,ans[1]);
   for (i=2;i<=tot;i++)
      printf(" %ld",ans[i]);
   printf("\n");
   end:
   return 0;
}
