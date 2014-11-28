#include <stdio.h>
#include <string.h>

char str[4005]={'\0'},tmp[4005]={'\0'};

int main()
{
   long i,j,k,l,s,flag;
   scanf("%ld%s",&k,str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      str[i+l]=str[i];
   for (i=l/2;i>=0;i--)
   {
      s=flag=0;
      for (j=1;j<=i;j++)
         s+=(str[j]!=str[j+i]);
      for (j=1;j<=l;j++)
      {
         if (s<=k)
         {
            if (!flag||strcmp(tmp,str+j)>0)
               strncpy(tmp,str+j,2*i);
            if (!flag)
               flag=1;
         }
         s+=(str[j+i]!=str[j+2*i])-(str[j]!=str[j+i]);
      }
      if (flag)
      {
         puts(tmp);
         break;
      }
   }
   return 0;
}
