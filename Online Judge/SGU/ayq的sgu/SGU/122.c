#include<stdio.h>

char str[5001]={'\0'},hash[1001]={'\0'};
long link[1001][1001]={0},du[1001]={0};

int main()
{
   long i,j,n,a,b;
   scanf("%ld\n",&n);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      j=0;
      while (!j||str[j]!='\0')
      {
         a=0;
         for (j++;str[j]>='0'&&str[j]<='9';j++)
            a=a*10+str[j]-'0';
         link[i][a]=1;
         du[a]++;
      }
   }
   a=hash[1]=1;
   printf("1");
   for (i=1;i<n;i++)
   {
      b=0;
      for (j=2;j<=n;j++)
         if (!hash[j]&&link[a][j]&&(!b||du[j]<du[b]))
            b=j;
      printf(" %ld",b);
      hash[a]=1;
      for (j=1;j<=n;j++)
         if (link[a][j])
            du[j]--;
      a=b;
   }
   printf(" 1\n");
   return 0;
}
