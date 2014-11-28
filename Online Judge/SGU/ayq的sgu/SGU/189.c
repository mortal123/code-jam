#include <stdio.h>
#include <string.h>

struct case1
{
   long l;
   char str[1005];
}v[101]={{0},{'\0'}};
struct case2
{
   long num,a,b;
};
char name[101][25]={'\0'},str[10005]={'\0'},tmp[1005]={'\0'},tmp2[1005]={'\0'};
long n;

struct case1 turn(char str[],long len)
{
   long i,f=0;
   struct case1 p=(struct case1){0,0};
   for (i=1;i<=len;i++)
   {
      if (str[i]=='"')
         f^=1;
      if (str[i]!=' '||f)
         p.str[++p.l]=str[i];
   }
   return p;
}

long find(char str[])
{
   long i;
   
   for (i=1;i<=n;i++)
      if (!strcmp(str+1,name[i]+1))
         return i;
   strcpy(name[++n]+1,str+1);
   return n;
}

struct case2 sub(char str2[])
{
   long i;
   struct case2 p;
   for (i=9;str2[i]!=',';i++)
      str[i-8]=str2[i];
   str[i-8]='\0';
   p.a=p.b=0;
   p.num=find(str);
   if (str2[++i]=='-')
   {
      for (i++;str2[i]>='0'&&str2[i]<='9';i++)
         p.a=p.a*10+str2[i]-'0';
      p.a=v[p.num].l-p.a+1;
   }
   else
   {
      for (;str2[i]>='0'&&str2[i]<='9';i++)
         p.a=p.a*10+str2[i]-'0';
      p.a++;
   }
   if (str2[i]==',')
   {
      if (str2[++i]=='-')
      {
         for (i++;str2[i]!=')';i++)
            p.b=p.b*10+str2[i]-'0';
         p.b=v[p.num].l-p.b;
      }
      else
      {
         for (;str2[i]!=')';i++)
            p.b=p.b*10+str2[i]-'0';
         if (p.b==0)
            p.b=v[p.num].l-p.b;
         else
            p.b+=p.a-1;
      }
   }
   else
      p.b=v[p.num].l;
   return p;
}

void print(struct case2 p)
{
   long i;
   for (i=p.a;i<=p.b;i++)
      printf("%c",v[p.num].str[i]);
   printf("\n");
}

int main()
{
   long i,j,m,a,b,s;
   struct case1 p;
   struct case2 p2,p3;
   scanf("%ld%ld\n",&n,&m);
   for (i=1;i<=n;i++)
   {
      gets(str+1);
      p=turn(str,strlen(str+1));
      for (j=2;p.str[j]!='=';j++)
         name[i][j-1]=p.str[j];
      for (j+=2;p.str[j]!='"';j++)
         v[i].str[++v[i].l]=p.str[j];
   }
   for (i=1;i<=m;i++)
   {
      gets(str+1);
      p=turn(str,strlen(str+1));
      if (p.str[1]=='p')
      {
         if (p.str[7]=='$')
         {
            for (j=8;p.str[j]!=')';j++)
               str[j-7]=p.str[j];
            str[j-7]='\0';
            puts(v[find(str)].str+1);
         }
         else
         {
            p2=sub(p.str+6);
            print(p2);
         }
      }
      else if (p.str[1]=='$')
      {
         for (j=2;p.str[j]!='=';j++)
            str[j-1]=p.str[j];
         str[j-1]='\0';
         a=find(str);
         if (p.str[j+1]=='$')
         {
            s=0;
            for (j+=2;p.str[j]!=';';j++)
               str[++s]=p.str[j];
            str[s+1]='\0';
            b=find(str);
            strcpy(v[a].str+1,v[b].str+1);
            v[a].l=v[b].l;
         }
         else
         {
            p2=sub(p.str+j);
            strncpy(v[a].str+1,v[p2.num].str+p2.a,p2.b-p2.a+1);
            v[a].str[p2.b-p2.a+2]='\0';
            v[a].l=p2.b-p2.a+1;
         }
      }
      else
      {
         p2=sub(p.str);
         j=1;
         while (p.str[j]!='=')
            j++;
         if (p.str[j+1]=='$')
         {
            s=0;
            for (j+=2;p.str[j]!=';';j++)
               str[++s]=p.str[j];
            str[s+1]='\0';
            a=find(str);
            strcpy(tmp,v[p2.num].str+p2.b+1);
            strcpy(tmp2,v[a].str+1);
            strcpy(v[p2.num].str+p2.a,tmp2);
            strcpy(v[p2.num].str+p2.a+v[a].l,tmp);
            v[p2.num].l+=v[a].l-p2.b+p2.a-1;
         }
         else
         {
            p3=sub(p.str+j);
            strcpy(tmp,v[p2.num].str+p2.b+1);
            strncpy(tmp2,v[p3.num].str+p3.a,p3.b-p3.a+1);
            tmp2[p3.b-p3.a+1]='\0';
            strcpy(v[p2.num].str+p2.a,tmp2);
            strcpy(v[p2.num].str+p2.a+p3.b-p3.a+1,tmp);
            v[p2.num].l+=p3.b-p3.a-p2.b+p2.a;
         }
      }
   }
   return 0;
}
