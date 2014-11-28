#include <stdio.h>
#define sign(a) ((a)>0?1:-1)
#define abb(a) ((a)>0?(a):(-(a)))

struct case1
{
   long son[36];
   long num;
}p[400001]={{0},{0}};
char str[301]={'\0'},tmp[301]={0},a[11]={'\0'},b[11]={'\0'},sign[301]={'\0'};
long f[60001]={0},num[60001]={0},stack[301]={0};
long totp=1,tot=0;

long getf(long now)
{
   if (f[now]==now)
      return now;
   return f[now]=getf(f[now]);
}

long find(long now,long len,long L,char ch[])
{
   long t,s;
   if (len>L)
   {
      if (p[now].num)
         return num[getf(p[now].num)];
      goto loop;
   }
   if (ch[len]>='a'&&ch[len]<='z')
      t=ch[len]-'a';
   else
      t=ch[len]-'0'+26;
   if (p[now].son[t]==0)
   {
      loop:
      if (ch[1]>='0'&&ch[1]<='9')
      {
         s=0;
         for (t=1;t<=L;t++)
            s=s*10+ch[t]-'0';
         return s;
      }
      return 0;
   }
   return find(p[now].son[t],len+1,L,ch);
}

long build(long now,long len,long L,char ch[])
{
   long t;
   if (len>L)
   {
      if (p[now].num==0)
      {
         p[now].num=++tot;
         f[tot]=tot;
         if (ch[1]>='0'&&ch[1]<='9')
            for (t=1;t<=L;t++)
               num[tot]=num[tot]*10+ch[t]-'0';
      }
      return p[now].num;
   }
   if (ch[len]>='a'&&ch[len]<='z')
      t=ch[len]-'a';
   else
      t=ch[len]-'0'+26;
   if (p[now].son[t]==0)
      p[now].son[t]=++totp;
   return build(p[now].son[t],len+1,L,ch);
}

long work(long a,long b,char sign)
{
   long i,s=1;
   if (sign=='+')
      return a+b;
   if (sign=='-')
      return a-b;
   if (sign=='*')
      return a*b;
   if (sign=='/')
      return a/b;
   if (sign=='%')
   {
      if (!a||!b)
         return 0;
      return abb(a)%abb(b)*sign(a)*sign(b);
   }
   if (a==1||!a)
      return a;
   if (a==-1)
      return 1-2*(b&1);
   for (i=1;i<=b;i++)
      s*=a;
   return s;
}

int main()
{
   long i,j,pa,pb,top,s;
   while (gets(str+1)!=NULL)
   {
      for (i=1;str[i]!='\0';i++)
         if (str[i]>='A'&&str[i]<='Z')
            str[i]-='A'-'a';
      if (str[1]=='d')
      {
         pa=pb=0;
         for (i=8;str[i]!=' ';i++)
            a[++pa]=str[i];
         while(str[i]==' ')
            i++;
         for (;str[i]!='\0'&&str[i]!=' ';i++)
            b[++pb]=str[i];
         pa=build(1,1,pa,a);
         pb=build(1,1,pb,b);
         if (f[pa]==pa)
            f[pa]=getf(pb);
      }
      else
      {
         pa=0;
         for (i=7;str[i]!='\0';i++)
            if (str[i]!=' ')
               tmp[++pa]=str[i];
         tmp[pa+1]='\0';
         top=s=0;
         for (i=1;tmp[i]!='\0';i++)
            if (tmp[i]>='a'&&tmp[i]<='z'||tmp[i]>='0'&&tmp[i]<='9')
            {
               pa=0;
               for (j=i;tmp[j]>='a'&&tmp[j]<='z'||tmp[j]>='0'&&tmp[j]<='9';j++)
                  a[++pa]=tmp[j];
               stack[++top]=find(1,1,pa,a);
               i=j-1;
            }
            else
            {
               if (tmp[i]=='-'&&(tmp[i-1]<'a'||tmp[i-1]>'z')&&(tmp[i-1]<'0'||tmp[i-1]>'9')&&tmp[i-1]!=')')
                  tmp[i]='!';
               else if (tmp[i]=='+'&&(tmp[i-1]<'a'||tmp[i-1]>'z')&&(tmp[i-1]<'0'||tmp[i-1]>'9')&&tmp[i-1]!=')')
                  continue;
               else if (tmp[i]=='*'||tmp[i]=='/'||tmp[i]=='%')
                  while (s&&sign[s]!='+'&&sign[s]!='-'&&sign[s]!='(')
                  {
                     if (sign[s]=='!')
                        stack[top]=-stack[top];
                     else
                     {
                        stack[top-1]=work(stack[top-1],stack[top],sign[s]);
                        top--;
                     }
                     s--;
                  }
               else if (tmp[i]=='+'||tmp[i]=='-')
                  while (s&&sign[s]!='(')
                  {
                     if (sign[s]=='!')
                        stack[top]=-stack[top];
                     else
                     {
                        stack[top-1]=work(stack[top-1],stack[top],sign[s]);
                        top--;
                     }
                     s--;
                  }
               else if (tmp[i]==')')
               {
                  while (sign[s]!='(')
                  {
                     if (sign[s]=='!')
                        stack[top]=-stack[top];
                     else
                     {
                        stack[top-1]=work(stack[top-1],stack[top],sign[s]);
                        top--;
                     }
                     s--;
                  }
                  s--;
               }
               if (tmp[i]!=')')
                  sign[++s]=tmp[i];
            }
         while (s)
         {
            if (sign[s]=='!')
               stack[top]=-stack[top];
            else
            {
               stack[top-1]=work(stack[top-1],stack[top],sign[s]);
               top--;
            }
            s--;
         }
         printf("%ld\n",stack[1]);
      }
   }
   return 0;
}
