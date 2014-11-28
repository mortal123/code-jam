#include <stdio.h>

long *p[4]={NULL};
char str[20]={0};

int main()
{
   long i,n;
   for (i=0;i<4;i++)
   {
      p[i]=(long*)malloc(sizeof(long));
      *p[i]=0;
   }
   scanf("%ld",&n);
   for (i=1;i<=n;i++)
   {
      scanf("%s",str+1);
      if (str[1]=='w')
         printf("%ld\n",*p[str[9]-'a']);
      else if (str[2]==':')
         p[str[1]-'a']=p[str[4]-'a'];
      else if (str[6]==';')
         *p[str[1]-'a']=str[5]-'0';
      else
         *p[str[1]-'a']=*p[str[5]-'a'];
   }
   return 0;
}
