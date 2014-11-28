#include <stdio.h>

long f[100001]={0},v[100001]={0},s[100001][2]={0};

long getf(long now)
{
   long tmp=f[now];
   if (f[now]==now)
      return now;
   f[now]=getf(f[now]);
   v[now]^=v[tmp];
   return f[now];
}

int main()
{
   long i,n,m,a,b,c,d,fa,fb,ans=0;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=n;i++)
      f[i]=i;
   for (i=1;i<=m;i++)
   {
      scanf("%ld%ld%ld%ld",&a,&b,&c,&d);
      fa=getf(a);
      fb=getf(b);
      if (fa!=fb)
      {
         f[fa]=fb;
         v[fa]=((v[a]!=v[b])^(c==d));
      }
      else if ((v[a]!=v[b])^(c==d))
         break;
   }
   if (i<=m)
      puts("NO");
   else
   {
      puts("YES");
      for (i=1;i<=n;i++)
      {
         fa=getf(i);
         s[fa][v[i]]++;
      }
      for (i=1;i<=n;i++)
         ans+=(s[f[i]][v[i]]<s[f[i]][!v[i]]||s[f[i]][v[i]]==s[f[i]][!v[i]]&&v[i]);
      printf("%ld\n",ans);
      for (i=1;i<=n;i++)
         if (s[f[i]][v[i]]<s[f[i]][!v[i]]||s[f[i]][v[i]]==s[f[i]][!v[i]]&&v[i])
            printf("%ld\n",i);
   }
   return 0;
}
