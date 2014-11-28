#include<stdio.h>
#include<string.h>

char str[21]={'\0'};
long num[10]={0};
long long s=0;
long l;

long long search(long now)
{
   long long t;
   long i;
   if (now==l+1)
      return (s%17)?-1:s;
   for (i=0;i<=9;i++)
      if (num[i]&&(now!=1||i))
      {
         s=s*10+i;
         num[i]--;
         t=search(now+1);
         if (t!=-1)
            return t;
         num[i]++;
         s/=10;
      }
   return -1;
}

int main()
{
   long i;
   scanf("%s",str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      num[str[i]-'0']++;
   printf("%I64d\n",search(1));
   return 0;
}
