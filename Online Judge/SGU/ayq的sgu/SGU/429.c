#include<stdio.h>

long a[6]={0},l[6][6]={0},r[6][6]={0};

int main()
{
   long i,j,n;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
      scanf("%ld",&a[i]);
   for (i=2;i<=n;i++)
      for (j=1;i+j-1<=n;j++)
      {
         if (l[j][i+j-2]>=r[j+1][i+j-1])
         {
            if (a[i+j-1]<r[j+1][i+j-1]||a[i+j-1]>l[j][i+j-2])
               l[j][i+j-1]=a[i+j-1];
            else if (a[i+j-1]==r[j+1][i+j-1])
               l[j][i+j-1]=0;
            else
               l[j][i+j-1]=a[i+j-1]-1;
            if (a[j]<r[j+1][i+j-1]||a[j]>l[j][i+j-2])
               r[j][i+j-1]=a[j];
            else if (a[j]==l[j][i+j-2])
               r[j][i+j-1]=0;
            else
               r[j][i+j-1]=a[j]+1;
         }
         else
         {
            if (a[i+j-1]>r[j+1][i+j-1]||a[i+j-1]<l[j][i+j-2])
               l[j][i+j-1]=a[i+j-1];
            else if (a[i+j-1]==r[j+1][i+j-1])
               l[j][i+j-1]=0;
            else
               l[j][i+j-1]=a[i+j-1]+1;
            if (a[j]>r[j+1][i+j-1]||a[j]<l[j][i+j-2])
               r[j][i+j-1]=a[j];
            else if (a[j]==l[j][i+j-2])
               r[j][i+j-1]=0;
            else
               r[j][i+j-1]=a[j]-1;
         }
      }
   if (l[1][n]==a[1])
      printf("SERGEY\n");
   else
      printf("FEDOR\n");
   return 0;
}
