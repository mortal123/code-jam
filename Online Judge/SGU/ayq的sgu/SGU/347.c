#include <stdio.h>
#include <string.h>

char name[105][105]={'\0'},t1[205]={'\0'},t2[205]={'\0'},ans[10005]={'\0'};

int main()
{
   long i,j,n;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
      gets(name[i]);
   for (i=1;i<n;i++)
      for (j=i+1;j<=n;j++)
      {
         strcpy(t1,name[i]);
         strcpy(t2,name[j]);
         strcat(t1,name[j]);
         strcat(t2,name[i]);
         if (strcmp(t1,t2)>0)
         {
            strcpy(t1,name[i]);
            strcpy(name[i],name[j]);
            strcpy(name[j],t1);
         }
      }
   for (i=1;i<=n;i++)
      strcat(ans,name[i]);
   puts(ans);
   return 0;
}
