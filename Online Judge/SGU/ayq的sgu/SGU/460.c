#include<stdio.h>
#include<string.h>

char str[31]={'\0'};

int main()
{
   long i,n,l;
   scanf("%ld",&n);
   getchar();
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      l=strlen(str+1);
      if (str[l]=='x'||str[l]=='s'||str[l]=='o'||str[l-1]=='c'&&str[l]=='h')
      {
         str[l+1]='e';
         str[l+2]='s';
         str[l+3]='\0';
      }
      else if (str[l]=='f')
      {
         str[l]='v';
         str[l+1]='e';
         str[l+2]='s';
         str[l+3]='\0';
      }
      else if (str[l-1]=='f'&&str[l]=='e')
      {
         str[l-1]='v';
         str[l+1]='s';
         str[l+2]='\0';
      }
      else if (str[l]=='y')
      {
         str[l]='i';
         str[l+1]='e';
         str[l+2]='s';
         str[l+3]='\0';
      }
      else
      {
         str[l+1]='s';
         str[l+2]='\0';
      }
      puts(str+1);
   }
   return 0;
}
