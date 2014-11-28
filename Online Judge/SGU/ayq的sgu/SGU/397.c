#include <stdio.h>
#include <string.h>

struct case1
{
   long last,next;
   char sign;
}p[1000005]={{0,0},{'\0'}};
char str[1000005]={'\0'};
long tot=1;

int main()
{
   long i,l,now=1;
   gets(str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
      if (str[i]=='L')
         now=((p[now].last)?p[now].last:now);
      else if (str[i]=='R')
         now=((p[now].next)?p[now].next:now);
      else
      {
         p[++tot]=(struct case1){now,p[now].next,str[i]};
         p[p[tot].last].next=p[p[tot].next].last=now=tot;
      }
   for (i=p[1].next;i;i=p[i].next)
      putchar(p[i].sign);
   return 0;
}
