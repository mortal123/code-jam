#include <stdio.h>
#include <string.h>

char str[1005]={'\0'};

int main()
{
   long i,j,k,n,l;
   scanf("%s%ld",str+1,&n);
   l=strlen(str+1);
   for (i=1;i<=n;i++)
   {
      for (j=1;j<l&&str[j]>=str[j+1];j++);
      for (k=j;k<l;k++)
         str[k]=str[k+1];
      l--;
   }
   for (i=1;i<=l;i++)
      printf("%c",str[i]);
   printf("\n");
   return 0;
}
