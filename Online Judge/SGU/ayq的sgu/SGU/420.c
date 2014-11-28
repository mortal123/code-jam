#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

struct case1
{
   long long lead;
   long num[10];
   long z,s;
}p[251]={0,0,0,0};

int main()
{
   long long l,r,t,ans=0;
   long i,j,k,a,b,flag,tot=0;
   scanf("%I64d%I64d",&l,&r);
   while (l<=r)
   {
      t=9;
      p[++tot].lead=l++;
      while (l+t<=r+1&&p[tot].lead%10==0)
      {
         l+=t;
         t*=10;
         p[tot].lead/=10;
         p[tot].z++;
      }
      p[tot].s=p[tot].z;
      t=p[tot].lead;
      while (t)
      {
         p[tot].num[t%10]++;
         p[tot].s++;
         t/=10;
      }
   }
   for (i=1;i<=tot;i++)
   {
      if (p[i].z==2)
         for (j=0;j<9;j++)
            for (k=j+1;k<=9;k++)
            {
               for (a=1;a<=tot;a++)
                  if (a!=i&&p[a].s==p[i].s)
                  {
                     for (b=0;b<=9&&p[a].num[b]<=p[i].num[b]+(j==b)+(k==b);b++);
                     if (b==10)
                        goto out;
                  }
               ans+=2;
               out:;
            }
      for (j=0;j<=9&&(!j||p[i].z);j++)
      {
         flag=0;
         for (a=1;a<=tot;a++)
            if (a!=i&&p[a].s==p[i].s)
            {
               for (b=0;b<=9&&p[a].num[b]<=p[i].num[b]+(j==b)*p[i].z;b++);
               if (b==10)
               {
                  k=0;
                  for (b=0;b<=9;b++)
                     k+=(p[a].num[b]<p[i].num[b]+(j==b)*p[i].z);
                  if (k>1||flag)
                     goto out2;
                  flag=1;
               }
            }
         ans+=flag;
         out2:;
      }
   }
   printf("%ld\n",ans);
   return 0;
}
