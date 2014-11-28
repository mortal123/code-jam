#include <stdio.h>

char str[100005]={0};

int main()
{
   long i,n,a,b,last,ans=0;
   scanf("%ld%s",&n,str+1);
   for (i=1;i<=n&&str[i]=='0';i++);
   if (i==n+1)
      printf("%s\n",(n&1)?"FIRST":"SECOND");
   else
   {
      a=0;
      while (str[a+1]=='0')
         a++;
      b=n+1;
      while (str[b-1]=='0')
         b--;
      ans=(a^(n+1-b));
      for (i=a+1;i<b;i++)
         if (str[i]=='0')
         {
            if (str[i+1]!='0'&&str[i+1]==last)
               ans^=1;
         }
         else
            last=str[i];
      printf("%s\n",ans?"FIRST":"SECOND");
   }
   return 0;
}
