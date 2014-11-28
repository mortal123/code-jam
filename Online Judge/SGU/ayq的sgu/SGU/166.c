#include <stdio.h>

struct case1
{
   long next,last;
   char a;
}p[21481]={{0,0},{'\0'}};
long len[1001]={0};
long x=1,y=0,now=1,tot=1,o=1000;

void insert(char ch)
{
   while (y>len[x])
   {
      p[++o].a=' ';
      p[o].last=now;
      p[now].next=o;
      now=o;
      len[x]++;
   }
   p[++o].a=ch;
   p[o].next=p[now].next;
   p[o].last=now;
   p[p[now].next].last=o;
   p[now].next=o;
   len[x]++;
   now=o;
   y++;
}

void left()
{
   if (y)
   {
      y--;
      if (y<len[x])
         now=p[now].last;
   }
}

void right()
{
   y++;
   if (p[now].next)
      now=p[now].next;
}

void up()
{
   long i;
   if (x>1)
   {
      now=--x;
      for (i=1;i<=y&&p[now].next;i++)
         now=p[now].next;
   }
}

void down()
{
   long i;
   if (x<tot)
   {
      now=++x;
      for (i=1;i<=y&&p[now].next;i++)
         now=p[now].next;
   }
}

void enter()
{
   long i;
   if (y>len[x])
      y=len[x];
   for (i=tot+1;i>=x+2;i--)
   {
      len[i]=len[i-1];
      p[i].next=p[i-1].next;
   }
   tot++;
   len[x+1]=len[x]-y;
   len[x]=y;
   p[x+1].next=p[now].next;
   p[p[now].next].last=x+1;
   p[now].next=0;
   now=++x;
   y=0;
}

void end()
{
   while (y<len[x])
   {
      now=p[now].next;
      y++;
   }
   if (y>len[x])
      y=len[x];
}

void home()
{
   y=0;
   now=x;
}

void back()
{
   long i;
   if (!y&&x>1)
   {
      for (i=x-1;p[i].next;i=p[i].next);
      p[i].next=p[now].next;
      p[p[now].next].last=i;
      y=len[x-1];
      len[x-1]+=len[x];
      now=i;
      for (i=x;i<tot;i++)
      {
         len[i]=len[i+1];
         p[i].next=p[i+1].next;
      }
      x--;
      tot--;
   }
   else if (y)
   {
      y--;
      if (y<len[x])
      {
         p[p[now].last].next=p[now].next;
         p[p[now].next].last=p[now].last;
         len[x]--;
         now=p[now].last;
      }
   }
}

void delete()
{
   long i;
   if (y>=len[x]&&x<tot)
   {
      while (y>len[x])
      {
         p[++o].a=' ';
         p[o].last=now;
         p[now].next=o;
         now=o;
         len[x]++;
      }
      p[now].next=p[x+1].next;
      p[p[now].next].last=now;
      len[x]+=len[x+1];
      for (i=x+1;i<tot;i++)
      {
         len[i]=len[i+1];
         p[i].next=p[i+1].next;
      }
      tot--;
   }
   else if (y<len[x])
   {
      p[p[p[now].next].next].last=now;
      p[now].next=p[p[now].next].next;
      len[x]--;
   }
}

int main()
{
   long i,j;
   char ch;
   while (1)
   {
      ch=getchar();
      if (ch=='L')
         left();
      else if (ch=='R')
         right();
      else if (ch=='U')
         up();
      else if (ch=='D')
         down();
      else if (ch=='N')
         enter();
      else if (ch=='E')
         end();
      else if (ch=='H')
         home();
      else if (ch=='X')
         delete();
      else if (ch=='B')
         back();
      else if (ch=='Q')
         break;
      else
         insert(ch);
   }
   for (i=1;i<=tot;i++)
   {
      for (j=p[i].next;j;j=p[j].next)
         printf("%c",p[j].a);
      if (i<tot)
         printf("\n");
   }
   return 0;
}
