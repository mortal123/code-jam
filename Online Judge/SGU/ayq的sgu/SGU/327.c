#include <stdio.h>
#include <string.h>
#define oo 1000000000

char str[15][2][32]={0},ans[905]={0};
long f[16385][15][2]={0},last[16385][15][2]={0},fit[15][2][15][2]={0},len[15]={0};

int main()
{
   long i,j,k,l,a,b,n,tot=0,s=0;
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%s",str[i][0]+1);
      len[i]=strlen(str[i][0]+1);
      for (j=1;j<=len[i];j++)
         str[i][1][j]=str[i][0][len[i]-j+1];
   }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (len[j]>len[i]&&(strstr(str[j][0]+1,str[i][0]+1)!=NULL||strstr(str[j][0]+1,str[i][1]+1)!=NULL))
         {
            for (k=i;k<n;k++)
            {
               len[k]=len[k+1];
               strcpy(str[k][0]+1,str[k+1][0]+1);
               strcpy(str[k][1]+1,str[k+1][1]+1);
            }
            i--;
            n--;
            break;
         }
   for (i=1;i<(1<<n);i++)
      for (j=1;j<=n;j++)
         for (k=0;k<=1;k++)
            f[i][j][k]=oo;
   for (i=0;i<=1;i++)
      for (j=1;j<=n;j++)
      {
         for (k=1;k<len[j];k++)
         {
            for (l=k;l<=len[j]&&str[j][i][l-k+1]==str[j][!i][l];l++);
            if (l>len[j])
               break;
         }
         f[1<<j-1][j][i]=len[j]+k-1;
      }
   for (i=1;i<=n;i++)
      for (j=1;j<=n;j++)
         if (i!=j)
            for (k=0;k<=1;k++)
               for (l=0;l<=1;l++)
               {
                  for (a=1;a<=len[i];a++)
                  {
                     for (b=1;b<=len[j]&&b+a-1<=len[i]&&str[j][l][b]==str[i][k][b+a-1];b++);
                     if (b>len[j]||b+a-1>len[i])
                        break;
                  }
                  fit[i][k][j][l]=len[j]-len[i]+a-1;
               }
   for (i=1;i<(1<<n)-1;i++)
      for (j=1;j<=n;j++)
         for (k=0;k<=1;k++)
            if (f[i][j][k]<oo)
               for (l=1;l<=n;l++)
                  if (!(i&(1<<l-1)))
                     for (a=0;a<=1;a++)
                        if (f[i][j][k]+fit[j][k][l][a]*2<f[i|(1<<l-1)][l][a])
                        {
                           f[i|(1<<l-1)][l][a]=f[i][j][k]+fit[j][k][l][a]*2;
                           last[i|(1<<l-1)][l][a]=k*n+j;
                        }
   a=0;
   for (i=1;i<=n;i++)
      for (j=0;j<=1;j++)
         if (!a||f[(1<<n)-1][i][j]<f[(1<<n)-1][a][b])
         {
            a=i;
            b=j;
         }
   tot=f[(1<<n)-1][a][b];
   i=(1<<n)-1;
   while (i)
      if (last[i][a][b])
      {
         j=(last[i][a][b]-1)%n+1;
         k=(last[i][a][b]>n);
         for (l=1;l<=fit[j][k][a][b];l++)
            ans[++s]=str[a][b][len[a]-l+1];
         i-=(1<<a-1);
         a=j;
         b=k;
      }
      else
      {
         for (l=1;l<=len[a];l++)
            ans[++s]=str[a][b][len[a]-l+1];
         i-=(1<<a-1);
      }
   while ((++s)<=tot)
      ans[s]=ans[tot-s+1];
   puts(ans+1);
   return 0;
}
