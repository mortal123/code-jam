#include <stdio.h>
#include <string.h>

long num[2049]={0},hash[11]={0},true[1029]={0};
char sign[2049]={'\0'},d[2049]={0},str[2055]={'\0'},list[11]={'\0'};

int main()
{
   long i,j,l,s=0,pn=0,ps=0,tot=0,top=0;
   scanf("%s",str+1);
   l=strlen(str+1);
   for (i=1;i<=l;i++)
   {
      if (str[i]>='a'&&str[i]<='j')
      {
         d[++tot]=str[i];
         if (!hash[str[i]-'a'+1])
         {
            hash[str[i]-'a'+1]=++s;
            list[s]=str[i];
         }
      }
      else if (str[i]==')')
      {
         while (sign[ps]!='(')
            d[++tot]=sign[ps--];
         ps--;
      }
      else
      {
         if (str[i]=='&')
            while (ps&&(sign[ps]=='!'||sign[ps]=='&'))
               d[++tot]=sign[ps--];
         else if (str[i]!='('&&str[i]!='!')
            while (ps&&sign[ps]!='(')
               d[++tot]=sign[ps--];
         sign[++ps]=str[i];
         if (str[i]=='='||str[i]=='|')
            i++;
         else if (str[i]=='<')
            i+=2;
      }
   }
   while (ps)
      d[++tot]=sign[ps--];
   for (i=0;i<(1<<s);i++)
   {
      top=0;
      for (j=1;j<=tot;j++)
         if (d[j]>='a'&&d[j]<='j')
            num[++top]=!!(i&(1<<(hash[d[j]-'a'+1]-1)));
         else if (d[j]=='!')
            num[top]^=1;
         else
         {
            if (d[j]=='&')
               num[top-1]&=num[top];
            else if (d[j]=='|')
               num[top-1]|=num[top];
            else if (d[j]=='#')
               num[top-1]^=num[top];
            else if (d[j]=='<')
               num[top-1]=(num[top-1]==num[top]);
            else
               num[top-1]=(!num[top-1]||num[top]);
            top--;
         }
      true[i]=num[1];
   }
   tot=0;
   for (i=0;i<(1<<s);i++)
      if (true[i])
      {
         if (tot)
            printf("||");
         tot++;
         for (j=1;j<=s;j++)
         {
            if (!(i&(1<<(j-1))))
               printf("!");
            printf("%c",list[j]);
            if (j<s)
               printf("&");
         }
      }
   if (!tot)
      printf("%c<=>!%c\n",list[1],list[1]);
   printf("\n");
   return 0;
}
