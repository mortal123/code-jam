#include <stdio.h>
#include <math.h>
#define eps 1e-10
#define pi 3.1415926535897932384626433832795
#define pi2 6.283185307179586476925286766559
#define pi3 1.5707963267948966192313216916398
#define pi4 0.15707963267948966192313216916398
#define dis(i,j) sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))

int x[801],y[801],p[1601],mod[1001];
double w[801],s[1601],dist[1601];

void qs(int x,int y)
{
   int i=x,j=y,t=p[(x+y)>>1];
   if (x>=y)
      return;
   p[(x+y)>>1]=p[x];
   while (i<j)
   {
      while(i<j&&w[p[j]]>w[t])
         j--;
      if(i<j)
         p[i++]=p[j];
      while(i<j&&w[p[i]]<w[t])
         i++;
      if(i<j)
         p[j--]=p[i];
   }
   p[i]=t;
   qs(x,i-1);
   qs(i+1,y);
}

int main()
{
   int n,i,j,k,t1,t2,ans=0;
   double t3;
   scanf("%d",&n);
   for(i=1;i<=n;i++)
      scanf("%d%d",&x[i],&y[i]);
   for(i=1;i<=1000;i++)
      mod[i]=i%10;
   for(i=1;i<=n;i++)
   {
      for(j=2;j<=n;j++)
      {
         p[j]=j-(j<=i);
         x[p[j]]-=x[i];
         y[p[j]]-=y[i];
         w[p[j]]=atan2(y[p[j]],x[p[j]]);
      }
      x[i]=y[i]=0;
      qs(2,n);
      for(j=2;j<=n;j++)
      {
         p[j+n-1]=p[j];
         s[j+n-1]=(s[j]=w[p[j]])+pi2;
         dist[j]=dist[j+n-1]=1/dis(i,p[j]);
      }
      for(j=2;j<=n;j++)
      {
         for(k=j+1;pi4>=s[k]-s[j];k++);
         t1=x[p[j]];
         t2=y[p[j]];
         t3=1000*dist[j];
         for(;s[k]-s[j]<pi3;k++)
            if (!((int)(pi3/(s[k]-s[j]))-mod[(int)((t1*x[p[k]]+t2*y[p[k]])*dist[k]*t3+eps)]))
               ans++;
      }
   }
   printf("%d\n",ans);
   return 0;
}
