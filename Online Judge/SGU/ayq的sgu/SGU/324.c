#include <stdio.h>
#include <string.h>

char str[105]={'\0'},ans[205]={'\0'};

int main()
{
   long i,q,l,s,tot,k,flag;
   scanf("%ld\n",&q);
   while (q--)
   {
      flag=tot=s=k=0;
      gets(str+1);
      l=strlen(str+1);
      for (i=1;i<=l;i++)
         if (str[i]=='-')
            s++;
         else if (str[i]==' ')
            k++;
         else
         {
            if ((!flag||str[i]=='"')&&s==1)
            {
               printf("error\n");
               goto end;
            }
            if (s==1)
               ans[++tot]='-';
            else if (s>1||k)
            {
               if (str[i]!='"'&&flag||s)
                  ans[++tot]=' ';
               while (s%3!=0)
               {
                  s-=2;
                  ans[++tot]='-';
                  ans[++tot]='-';
                  ans[++tot]=' ';
               }
               while (s)
               {
                  s-=3;
                  ans[++tot]='-';
                  ans[++tot]='-';
                  ans[++tot]='-';
                  ans[++tot]=' ';
               }
            }
            if (str[i]!='"')
               flag=1;
            ans[++tot]=str[i];
            s=k=0;
         }
      ans[++tot]='\0';
      puts(ans+1);
      end:;
   }
   return 0;
}
