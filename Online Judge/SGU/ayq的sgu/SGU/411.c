#include <stdio.h>
#include <string.h>

char a[2005]={0},b[2005]={0},tmp[2005]={0},f[2002][2002]={0};

int main()
{
   long i,j,la,lb;
   scanf("%s%s",a+1,b+1);
   la=strlen(a+1);
   lb=strlen(b+1);
   for (i=1;i<=la;i++)
      f[i][i]=f[i][i-1]=1;
   for (i=2;i<=la;i++)
      for (j=1;i+j-1<=la;j++)
         if (f[j+1][i+j-2]&&a[j]==a[i+j-1])
            f[j][i+j-1]=1;
   for (i=la;i>=1;i--)
      for (j=1;i+j-1<=la;j++)
         if (f[j][i+j-1])
         {
            strncpy(tmp+1,a+j,i);
            tmp[i+1]=0;
            if (strstr(b+1,tmp+1)!=NULL)
            {
               puts(tmp+1);
               goto end;
            }
         }
   end:
   return 0;
}
