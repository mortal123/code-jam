#include <stdio.h>

struct case1
{
   long a,b;
}p[150001]={0,0};
char str[100]={0},lm[100001]={0},lp[100001]={0};
long du[100001]={0},pair[100001]={0};

int main()
{
   long i,j,n,m,a,b,mid;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=m;i++)
   {
      gets(str+1);
      for (j=1;str[j]>='0'&&str[j]<='9';j++)
         p[i].a=p[i].a*10+str[j]-'0';
      for (j++;str[j]>='0'&&str[j]<='9';j++)
         p[i].b=p[i].b*10+str[j]-'0';
      du[p[i].a]++;
      du[p[i].b]++;
   }
   for (mid=1;mid<n&&du[mid]==2;mid++);
   for (i=1;i<=m;i++)
      if (p[i].a!=mid&&p[i].b!=mid)
      {
         pair[p[i].a]=p[i].b;
         pair[p[i].b]=p[i].a;
      }
   while (gets(str+1)!=NULL)
      if (str[1]=='L')
      {
         a=b=0;
         for (j=8;str[j]>='0'&&str[j]<='9';j++)
            a=a*10+str[j]-'0';
         for (j++;str[j]>='0'&&str[j]<='9';j++)
            b=b*10+str[j]-'0';
         if (a==b)
            puts("0");
         else if (a==mid)
         {
            if (!lm[b])
               puts("1");
            else if (!lp[b]&&!lm[pair[b]])
               puts("2");
            else
               puts("-1");
         }
         else if (b==mid)
         {
            if (!lm[a])
               puts("1");
            else if (!lp[a]&&!lm[pair[a]])
               puts("2");
            else
               puts("-1");
         }
         else if (pair[a]==b)
         {
            if (!lp[a])
               puts("1");
            else if (!lm[a]&&!lm[b])
               puts("2");
            else
               puts("-1");
         }
         else if (!lm[a]&&!lm[b])
            puts("2");
         else if (!lp[a]&&!lm[pair[a]]&&!lm[b]||!lp[b]&&!lm[pair[b]]&&!lm[a])
            puts("3");
         else if (!lp[a]&&!lm[pair[a]]&&!lp[b]&&!lm[pair[b]])
            puts("4");
         else
            puts("-1");
      }
      else
      {
         a=0;
         for (j=8;str[j]>='0'&&str[j]<='9';j++)
            a=a*10+str[j]-'0';
         if (p[a].a==mid)
            lm[p[a].b]=1;
         else if (p[a].b==mid)
            lm[p[a].a]=1;
         else
            lp[p[a].a]=lp[p[a].b]=1;
      }
   return 0;
}
