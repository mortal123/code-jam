#include<stdio.h>
#include<string.h>

char str[2005]={'\0'};
long p[2005]={0};

int main()
{
   long i,j,l;
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      p[i]=str[l-i+1]-'0';
   for (i=l;i>=1;i--)
   {
      p[i-1]+=(p[i]&1)*10;
      p[i]/=2;
   }
   if (((str[l]-'0')&1)==0)
   {
      p[1]--;
      for (i=2;i<=l;i++)
      {
         p[i]+=(p[i-1]+10)/10-1;
         p[i-1]=(p[i-1]+10)%10;
      }
      if ((p[1]&1)==0)
      {
         p[1]--;
         for (i=2;i<=l;i++)
         {
            p[i]+=(p[i-1]+10)/10-1;
            p[i-1]=(p[i-1]+10)%10;
         }
      }
   }
   for (i=l,j=0;i>=1;i--)
   {
      if (p[i])
         j=1;
      if (j)
         printf("%ld",p[i]);
   }
   printf("\n");
   return 0;
}
