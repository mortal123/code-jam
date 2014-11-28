#include <stdio.h>
#include <string.h>
#define mod 1000000007
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

long v[100005]={0},rev[100005]={0};
char str[3][100005]={0};

long mi(long a,long b)
{
   long t;
   if (!b)
      return 1;
   t=mi(a,b>>1);
   t=(long long)t*t%mod;
   if (b&1)
      t=(long long)t*a%mod;
   return t;
}

int main()
{
   long i,n,p0=0,p1=0,p2=0,p3=0,m1=0,m2,a,b,ans=0;
   gets(str[0]+1);
   gets(str[1]+1);
   gets(str[2]+1);
   n=strlen(str[0]+1);
   v[0]=rev[0]=1;
   for (i=1;i<=n;i++)
   {
      v[i]=(long long)v[i-1]*i%mod;
      rev[i]=mi(v[i],mod-2);
   }
   for (i=1;i<=n;i++)
      if (str[0][i]=='0'&&str[1][i]=='0'&str[2][i]=='0'||str[0][i]=='1'&&str[1][i]=='1'&str[2][i]=='1')
         p0++;
      else if (str[0][i]=='1'&&str[1][i]=='0'&str[2][i]=='0'||str[0][i]=='0'&&str[1][i]=='1'&str[2][i]=='1')
         p1++;
      else if (str[0][i]=='0'&&str[1][i]=='1'&str[2][i]=='0'||str[0][i]=='1'&&str[1][i]=='0'&str[2][i]=='1')
         p2++;
      else
         p3++;
   if ((p1&1)==(p2&1)&&(p2&1)==(p3&1))
   {
      m2=p1;
      m1=max(m1,(p1-p2)/2);
      m2=min(m2,(p1+p2)/2);
      m1=max(m1,(p1-p3)/2);
      m2=min(m2,(p1+p3)/2);
      for (i=m1;i<=m2;i++)
      {
         a=(p2-p1)/2+i;
         b=(p3-p1)/2+i;
         ans=(ans+(long long)v[p1]*v[p2]%mod*v[p3]%mod*rev[i]%mod*rev[a]%mod*rev[b]%mod*rev[p1-i]%mod*rev[p2-a]%mod*rev[p3-b])%mod;
      }
   }
   while (p0--)
      ans=ans*2%mod;
   printf("%ld\n",ans);
   return 0;
}
