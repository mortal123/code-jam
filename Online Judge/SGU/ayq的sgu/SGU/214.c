#include <stdio.h>
#include <string.h>
#define oo 1000000000

char str[205]={'\0'},a[2005]={'\0'},b[2005]={'\0'},ans1[4005]={'\0'},ans2[4005]={'\0'};
long turn[257]={0},f[2001][2001]={0},last[2001][2001]={0},c[201][201]={0},min1[201]={0},rec1[201]={0},min2[201]={0},rec2[201]={0};

int main()
{
   long i,j,l,l1,l2,top1,top2;
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      turn[str[i]+128]=i;
   gets(a+1);
   l1=strlen(a+1);
   gets(b+1);
   l2=strlen(b+1);
   for (i=1;i<=l;i++)
      min1[i]=min2[i]=oo;
   for (i=1;i<=l;i++)
      for (j=1;j<=l;j++)
      {
         scanf("%ld",&c[i][j]);
         if (c[i][j]<min1[i])
         {
            min1[i]=c[i][j];
            rec1[i]=j;
         }
         if (c[i][j]<min2[j])
         {
            min2[j]=c[i][j];
            rec2[j]=i;
         }
      }
   for (i=0;i<=l1;i++)
      for (j=0;j<=l2;j++)
         if (i|j)
         {
            f[i][j]=oo;
            if (i&&j)
               f[i][j]=f[i-1][j-1]+c[turn[a[i]+128]][turn[b[j]+128]];
            if (i&&f[i-1][j]+min1[turn[a[i]+128]]<f[i][j])
            {
               f[i][j]=f[i-1][j]+min1[turn[a[i]+128]];
               last[i][j]=1;
            }
            if (j&&f[i][j-1]+min2[turn[b[j]+128]]<f[i][j])
            {
               f[i][j]=f[i][j-1]+min2[turn[b[j]+128]];
               last[i][j]=2;
            }
         }
   printf("%ld\n",f[l1][l2]);
   top1=top2=l1+l2;
   i=l1;
   j=l2;
   while (i|j)
      if (!last[i][j])
      {
         ans1[--top1]=a[i--];
         ans2[--top2]=b[j--];
      }
      else if (last[i][j]==1)
      {
         ans1[--top1]=a[i];
         ans2[--top2]=str[rec1[turn[a[i--]+128]]];
      }
      else if (last[i][j]==2)
      {
         ans1[--top1]=str[rec2[turn[b[j]+128]]];
         ans2[--top2]=b[j--];
      }
   puts(ans1+top1);
   puts(ans2+top2);
   return 0;
}
