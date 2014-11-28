#include <stdio.h>
#include <string.h>
#define oo 1000000000
#define min(a,b) ((a)<(b)?(a):(b))

long num[3005]={0},a[12005]={0},f[12005][2]={0};
char str[3005]={0};

int main()
{
   long i,b,l,s=0;
   scanf("%s%ld",str+1,&b);
   if (b==1)
   {
      puts(str+1);
      goto end;
   }
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      num[i]=str[l-i+1]-'0';
   while (l)
   {
      for (i=l-1;i>=0;i--)
      {
         num[i]+=num[i+1]%b*10;
         num[i+1]/=b;
      }
      a[++s]=num[0]/10;
      num[0]=0;
      while (l&&!num[l])
         l--;
   }
   f[0][1]=oo;
   for (i=1;i<=s+1;i++)
   {
      f[i][1]=min(b-a[i]+f[i-1][0],b-1-a[i]+f[i-1][1]);
      f[i][0]=min(a[i]+f[i-1][0],a[i]+1+f[i-1][1]);
   }
   printf("%ld\n",f[s+1][0]);
   end:
   return 0;
}
