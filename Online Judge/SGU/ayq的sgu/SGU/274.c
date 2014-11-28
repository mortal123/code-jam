#include <stdio.h>
#include <string.h>
#define max(a,b) ((a)>(b)?(a):(b))

char str[105]={'\0'},tmp[105]={'\0'};

long letter(long x)
{
   return str[x]>='a'&&str[x]<='z'||str[x]>='A'&&str[x]<='Z';
}

long symbol(long x)
{
   return letter(x)||str[x]>='0'&&str[x]<='9'||str[x]=='_'||str[x]=='-'||str[x]=='.';
}

long address(long len)
{
   long i,s=0;
   for (i=1;i<=len;i++)
   {
      if (!symbol(i)&&str[i]!='@'||str[i]=='.'&&(str[i+1]=='.'||i==1))
         return 0;
      if (str[i]=='@')
      {
         if (s||str[i+1]=='.'||str[i-1]=='.'||i==1)
            return 0;
         else
            s=i;
      }
   }
   if (!s)
      return 0;
   if (len>3&&str[len-3]=='.')
   {
      if (s<len-4&&letter(len)&&letter(len-1)&&letter(len-2))
         return 1;
   }
   if (len>2&&str[len-2]=='.')
   {
      if (s<len-3&&letter(len)&&letter(len-1))
         return 1;
   }
   return 0;
}

int main()
{
   long i,q,l;
   scanf("%ld\n",&q);
   while (q--)
   {
      gets(str+1);
      l=strlen(str+1);
      if (address(l))
         printf("YES\n");
      else
         printf("NO\n");
   }
   return 0;
}
