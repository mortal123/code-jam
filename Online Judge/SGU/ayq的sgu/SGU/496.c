#include<stdio.h>
#define dj(x1,x2,y1,y2) ((x1)*(x2)+(y1)*(y2))

long X1[5001]={0},Y1[5001]={0},X2[5001]={0},Y2[5001]={0};

int main()
{
   long i,j,n,ans=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld%ld%ld%ld",&X1[i],&Y1[i],&X2[i],&Y2[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
      {
         if (X1[i]==X1[j]&&Y1[i]==Y1[j])
         {
            if (dj(X2[i]-X1[i],X2[j]-X1[j],Y2[i]-Y1[i],Y2[j]-Y1[j])==0)
               ans++;
         }
         else if (X1[i]==X2[j]&&Y1[i]==Y2[j])
         {
            if (dj(X2[i]-X1[i],X1[j]-X2[j],Y2[i]-Y1[i],Y1[j]-Y2[j])==0)
               ans++;
         }
         else if (X2[i]==X1[j]&&Y2[i]==Y1[j])
         {
            if (dj(X1[i]-X2[i],X2[j]-X1[j],Y1[i]-Y2[i],Y2[j]-Y1[j])==0)
               ans++;
         }
         else if (X2[i]==X2[j]&&Y2[i]==Y2[j])
         {
            if (dj(X1[i]-X2[i],X1[j]-X2[j],Y1[i]-Y2[i],Y1[j]-Y2[j])==0)
               ans++;
         }
      }
   printf("%ld\n",ans);
   return 0;
}
