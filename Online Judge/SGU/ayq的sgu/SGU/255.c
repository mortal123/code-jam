#include <stdio.h>
#include <math.h>

int main()
{
   long long q,m,t;
   scanf("%I64d",&q);
   while (q--)
   {
      scanf("%I64d",&m);
      m=8*m-7;
      if (m<=1)
         printf("NO\n");
      else
      {
         t=sqrt(m+1e-20);
         if (t*t!=m||!(t&1))
            printf("NO\n");
         else
            printf("YES\n");
      }
   }
   return 0;
}
