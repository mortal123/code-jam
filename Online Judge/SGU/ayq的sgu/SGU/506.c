#include<stdio.h>
#include<string.h>

long next[100001][26]={0},p[26]={0};
char str1[100005]={'\0'},str2[105]={'\0'};
long l2;

long get_end(long st)
{
   long i;
   for (i=1;i<=l2;i++)
   {
      st=next[st][str2[i]-'a'];
      if (!st)
         return 0;
   }
   return st;
}

int main()
{
   long long ans=0;
   long i,j,l1,end;
   gets(str1+1);
   l1=strlen(str1+1);
   gets(str2+1);
   l2=strlen(str2+1);
   for (i=l1;i>=0;i--)
   {
      for (j=0;j<=25;j++)
         next[i][j]=p[j];
      p[str1[i]-'a']=i;
   }
   end=get_end(0);
   for (i=1;i<=l1-l2+1;i++)
   {
      if (!end)
         break;
      ans+=l1-end+1;
      if (str1[i]==str2[1])
         end=get_end(i);
   }
   printf("%I64d\n",ans);
   return 0;
}
