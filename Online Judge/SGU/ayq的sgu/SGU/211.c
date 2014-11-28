#include <stdio.h>

long a[1001]={0};

int main()
{
   long i,j,n,m,p,next;
   scanf("%ld%ld",&n,&m);
   for (i=1;i<=m;i++)
   {
      scanf("%ld",&p);
      next=0;
      for (j=p+1;j<=n;j++)
         if (a[j]==2)
         {
            next=j;
            break;
         }
      if (!a[p])
      {
         if (next)
            printf("3 %ld %ld %ld %ld %ld %ld\n",next,a[next]-=2,next+1,++a[next+1],p,++a[p]);
         else
            printf("1 %ld %ld\n",p,++a[p]);
      }
      else if (a[p]==1&&a[p+1]==0)
         printf("2 %ld %ld %ld %ld\n",p,--a[p],p+1,++a[p+1]);
      else if (a[p]==1&&a[p+1]==1)
      {
         if (next)
            printf("4 %ld %ld %ld %ld %ld %ld %ld %ld\n",next,a[next]-=2,next+1,++a[next+1],p,--a[p],p+1,++a[p+1]);
         else
            printf("2 %ld %ld %ld %ld\n",p,--a[p],p+1,++a[p+1]);
      }
      else if (a[p]==1&&a[p+1]==2)
      {
         printf("4 %ld %ld %ld %ld %ld %ld ",p+1,a[p+1]-=2,p+2,++a[p+2],p,--a[p]);
         printf("%ld %ld\n",p+1,++a[p+1]);
      }
      else
         printf("2 %ld %ld %ld %ld\n",p,--a[p],p+1,++a[p+1]);
   }
   return 0;
}
