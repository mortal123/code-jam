#include <stdio.h>
#include <string.h>

char str[1000005];
int n,l;
int fdic();

int fstr(int st,int add)
{
   int i;
   long long s=0;
   if (st+add+1>n)
   {
      printf("Error at position %d!",st-1);
      return 0;
   }
   if (str[st]=='0'&&str[st+1]!=':')
   {
      printf("Error at position %d!",st);
      return 0;
   }
   for (i=st;str[i]>='0'&&str[i]<='9';i++)
   {
      s=s*10+str[i]-'0';
      if (i+add+1+s>n)
      {
         printf("Error at position %d!",i-1);
         return 0;
      }
   }
   if (str[i]!=':')
   {
      printf("Error at position %d!",i-1);
      return 0;
   }
   if (i+s>l)
   {
      printf("Error at position %d!",l);
      return 0;
   }
   return i+s;
}

int fint(int st,int add)
{
   int i;
   if (st+add+2>n)
   {
      printf("Error at position %d!",st-1);
      return 0;
   }
   if (str[st+1]<'0'||str[st+1]>'9')
   {
      printf("Error at position %d!",st);
      return 0;
   }
   if (str[st+1]=='0'&&str[st+2]>='0'&&str[st+2]<='9')
   {
      printf("Error at position %d!",st+1);
      return 0;
   }
   for (i=st+1;str[i]>='0'&&str[i]<='9';i++)
      if (i+add+1>n)
      {
         printf("Error at position %d!",i-1);
         return 0;
      }
   if (str[i]!='e')
   {
      printf("Error at position %d!",i-1);
      return 0;
   }
   return i;
}

int flis(int st,int add)
{
   int i=st+1;
   if (st+add+1>n)
   {
      printf("Error at position %d!",st-1);
      return 0;
   }
   while (1)
   {
      if (str[i]>='0'&&str[i]<='9')
         i=fstr(i,add+1);
      else if (str[i]=='i')
         i=fint(i,add+1);
      else if (str[i]=='l')
         i=flis(i,add+1);
      else if (str[i]=='d')
         i=fdic(i,add+1);
      else if (str[i]=='e')
         return i;
      else
      {
         printf("Error at position %d!",i-1);
         return 0;
      }
      if (!i)
         return 0;
      i++;
   }
}

int fdic(int st,int add)
{
   int i=st+1;
   if (st+add+1>n)
   {
      printf("Error at position %d!",st-1);
      return 0;
   }
   while (1)
   {
      if (str[i]>='0'&&str[i]<='9')
         i=fstr(i,add+3);
      else if (str[i]=='i')
         i=fint(i,add+3);
      else if (str[i]=='l')
         i=flis(i,add+3);
      else if (str[i]=='d')
         i=fdic(i,add+3);
      else if (str[i]=='e')
         return i;
      else
      {
         printf("Error at position %d!",i-1);
         return 0;
      }
      if (!i)
         return 0;
      i++;
      if (str[i]>='0'&&str[i]<='9')
         i=fstr(i,add+1);
      else if (str[i]=='i')
         i=fint(i,add+1);
      else if (str[i]=='l')
         i=flis(i,add+1);
      else if (str[i]=='d')
         i=fdic(i,add+1);
      else
      {
         printf("Error at position %d!",i-1);
         return 0;
      }
      if (!i)
         return 0;
      i++;
   }
}

int main()
{
   int t;
   scanf("%d\n",&n);
   gets(str+1);
   l=strlen(str+1);
   if (str[1]>='0'&&str[1]<='9'||str[1]=='i'||str[1]=='l'||str[1]=='d')
   {
      if (str[1]>='0'&&str[1]<='9')
         t=fstr(1,0);
      else if (str[1]=='i')
         t=fint(1,0);
      else if (str[1]=='l')
         t=flis(1,0);
      else
         t=fdic(1,0);
      if (t==l)
         puts("ok");
      else if (t)
         printf("Error at position %d!",t);
   }
   else
      puts("Error at position 0!");
   return 0;
}
