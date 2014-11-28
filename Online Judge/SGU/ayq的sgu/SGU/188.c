#include<stdio.h>
#define abb(a) ((a)>0?(a):(-(a)))

long ans[21]={0},pos[21]={0},v[21]={0};

int main()
{
   long i,j,n,t;
   scanf("%ld%ld",&n,&t);
   for (i=1;i<=n;i++)
      scanf("%ld",&pos[i]);
   for (i=1;i<=n;i++)
      scanf("%ld",&v[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
         if (v[i]*v[j]<0)
         {
            if (v[i]>v[j])
            {
               ans[i]+=((v[i]-v[j])*t+(pos[i]-pos[j]+1000)%1000)/1000;
               ans[j]+=((v[i]-v[j])*t+(pos[i]-pos[j]+1000)%1000)/1000;
            }
            else
            {
               ans[i]+=((v[j]-v[i])*t+(pos[j]-pos[i]+1000)%1000)/1000;
               ans[j]+=((v[j]-v[i])*t+(pos[j]-pos[i]+1000)%1000)/1000;
            }
         }
   for (i=1;i<=n;i++)
      printf("%ld%c",ans[i],(i==n)?'\n':' ');
   return 0;
}
